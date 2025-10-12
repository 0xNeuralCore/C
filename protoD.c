#include "protoD.h"
#include <string.h>
#include <stdio.h> /* printf */

static TYP_ELEMENT_ENTRY S_st_table_entry[MAX_ELEMENTS];
static TYP_ELEMENT_ENTRY *S_st_hash_table[HASH_SIZE] = {0};
static uint16_t S_u16_item_count = 0U;

/**
 * F_hash_4tuple_fast()
 */
static inline uint32_t F_hash_4tuple_fast(const uint8_t ip_src[4],
                                          uint16_t port_src,
                                          const uint8_t ip_dst[4],
                                          uint16_t port_dst)
{
    uint32_t src32, dst32;
    memcpy(&src32, ip_src, sizeof(src32));
    memcpy(&dst32, ip_dst, sizeof(dst32));

    uint32_t h = src32 ^ (dst32 * 0x45d9f3bU);
    h ^= ((uint32_t)port_src << 16) | (uint32_t)port_dst;
    h *= 0x119de1f3U;
    h ^= (h >> 16);

    return h % HASH_SIZE;
}

/**
 * F_hash_function()
 */
uint32_t F_hash_function(const uint8_t tu08_ip_src[4], uint16_t u16_port_src,
                         const uint8_t tu08_ip_dst[4], uint16_t u16_port_dst)
{
    return F_hash_4tuple_fast(tu08_ip_src, u16_port_src, tu08_ip_dst, u16_port_dst);
}

/**
 * F_add_element()
 */
bool F_add_element(const uint8_t ip_src[4], uint16_t port_src,
                   const uint8_t ip_dst[4], uint16_t port_dst,
                   uint64_t u64_value)
{
    if (S_u16_item_count >= MAX_ELEMENTS)
        return false;

    uint32_t u32_index = F_hash_function(ip_src, port_src, ip_dst, port_dst);

    for (uint32_t i = 0; i < MAX_ELEMENTS; i++)
    {
        if (!S_st_table_entry[i].b_used)
        {
            S_st_table_entry[i].b_used = true;
            memcpy(S_st_table_entry[i].tu08_ip_src, ip_src, 4);
            S_st_table_entry[i].u16_port_src = port_src;
            memcpy(S_st_table_entry[i].tu08_ip_dst, ip_dst, 4);
            S_st_table_entry[i].u16_port_dst = port_dst;
            S_st_table_entry[i].u64_value = u64_value;
            S_st_table_entry[i].p_next = NULL;

            TYP_ELEMENT_ENTRY *p_head = S_st_hash_table[u32_index];
            if (p_head == NULL)
            {
                S_st_hash_table[u32_index] = &S_st_table_entry[i];
            }
            else
            {
                TYP_ELEMENT_ENTRY *p_current = p_head;
                while (p_current->p_next != NULL)
                    p_current = p_current->p_next;
                p_current->p_next = &S_st_table_entry[i];
            }
            S_u16_item_count++;
            return true;
        }
    }

    return false;
}

/**
 * F_search_element()
 */
bool F_search_element(const uint8_t ip_src[4], uint16_t port_src,
                      const uint8_t ip_dst[4], uint16_t port_dst,
                      uint64_t *p_u64_found_value)
{
    if (p_u64_found_value == NULL)
        return false;

    uint32_t u32_index = F_hash_function(ip_src, port_src, ip_dst, port_dst);
    TYP_ELEMENT_ENTRY *p_current = S_st_hash_table[u32_index];

    while (p_current != NULL)
    {
        if (memcmp(p_current->tu08_ip_src, ip_src, 4) == 0 &&
            p_current->u16_port_src == port_src &&
            memcmp(p_current->tu08_ip_dst, ip_dst, 4) == 0 &&
            p_current->u16_port_dst == port_dst)
        {
            *p_u64_found_value = p_current->u64_value;
            return true;
        }
        p_current = p_current->p_next;
    }

    return false;
}

/**
 * main()
 */
int main(void)
{
    uint8_t ip1_src[4] = {192, 168, 1, 1};
    uint8_t ip1_dst[4] = {10, 0, 0, 1};

    uint8_t ip2_src[4] = {192, 168, 1, 2};
    uint8_t ip2_dst[4] = {10, 0, 0, 2};

    F_add_element(ip1_src, 1234, ip1_dst, 80, 100);
    F_add_element(ip2_src, 5678, ip2_dst, 443, 200);

    uint64_t val = 0;

    if (F_search_element(ip1_src, 1234, ip1_dst, 80, &val))
        printf("Found flow 1: %lu\n", val);
    else
        printf("Flow 1 not found\n");

    if (F_search_element(ip2_src, 5678, ip2_dst, 443, &val))
        printf("Found flow 2: %lu\n", val);
    else
        printf("Flow 2 not found\n");

    return 0;
}
