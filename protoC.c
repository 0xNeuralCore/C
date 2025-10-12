#include "protoC.h"
#include <stdio.h> /* printf */

#define HASH_SIZE 100U

static TYP_ELEMENT_ENTRY S_st_table_entry[MAX_ELEMENTS];
static TYP_ELEMENT_ENTRY *S_st_hash_table[HASH_SIZE] = {0};
static uint16_t S_u16_item_count = 0U;

/**
 * @brief Simple hash function using modulo HASH_SIZE
 * @param u32_key Key to hash
 * @return Hash table index
 */
static uint32_t F_hash_function(uint32_t u32_key);

/**
 * F_hash_function()
 */
static uint32_t F_hash_function(uint32_t u32_key)
{
    return u32_key % HASH_SIZE;
}

/**
 * F_add_element()
 */
bool F_add_element(uint32_t u32_id, uint64_t u64_value)
{
    bool b_rc = false;
    uint32_t u32_index = 0U;
    bool b_continue_loop = true;

    if (S_u16_item_count < MAX_ELEMENTS)
    {
        u32_index = F_hash_function(u32_id);

        /* Search for a free slot in the main table */
        for (uint32_t i = 0U; i < MAX_ELEMENTS && b_continue_loop; i++)
        {
            if (!S_st_table_entry[i].b_used)
            {
                /* Initialize the new entry */
                S_st_table_entry[i].b_used = true;
                S_st_table_entry[i].u32_id = u32_id;
                S_st_table_entry[i].u64_value = u64_value;
                S_st_table_entry[i].p_next = NULL;

                /* Handle collision */
                TYP_ELEMENT_ENTRY *p_head = S_st_hash_table[u32_index];

                if (p_head == NULL)
                {
                    /* No collision: direct placement */
                    S_st_hash_table[u32_index] = &S_st_table_entry[i];
                }
                else
                {
                    /* Collision: insert at the end of the list */
                    TYP_ELEMENT_ENTRY *p_current = p_head;
                    while (p_current->p_next != NULL)
                    {
                        p_current = p_current->p_next;
                    }
                    p_current->p_next = &S_st_table_entry[i];
                }

                S_u16_item_count++;
                b_rc = true;
                b_continue_loop = false;
            }
        }
    }

    return b_rc;
}

/**
 * F_search_element()
 */
bool F_search_element(uint32_t u32_search_id, uint64_t *p_u64_found_value)
{
    bool b_rc = false;
    bool b_continue_loop = true;

    if (p_u64_found_value != NULL)
    {
        uint32_t u32_index = F_hash_function(u32_search_id);
        TYP_ELEMENT_ENTRY *p_current = S_st_hash_table[u32_index];

        /* Traverse the linked list at this index */
        while (p_current != NULL && b_continue_loop)
        {
            if (p_current->u32_id == u32_search_id)
            {
                *p_u64_found_value = p_current->u64_value;
                b_rc = true;
                b_continue_loop = false;
            }
            p_current = p_current->p_next;
        }
    }

    return b_rc;
}

/**
 * main()
 */
int main(void)
{
    (void)F_add_element(1000U, 84U);
    (void)F_add_element(1100U, 123U);

    uint64_t u64_value = 0U;
    if (F_search_element(1000U, &u64_value))
        printf("ID 1000 -> value = %lu\n", u64_value);
    else
        printf("ID 1000 not found\n");

    uint64_t u64_value2 = 0U;
    if (F_search_element(1100U, &u64_value2))
        printf("ID 1100 -> value = %lu\n", u64_value2);
    else
        printf("ID 1100 not found\n");

    return 0;
}
