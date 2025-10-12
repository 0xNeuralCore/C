#include "protoB.h"
#include <stdio.h> /* printf */

static TYP_ELEMENT_ENTRY S_st_table_entry[MAX_ELEMENTS];
static TYP_ELEMENT_ENTRY *S_st_hash_table[MAX_ELEMENTS] = {0};
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
    return u32_key % MAX_ELEMENTS;
}

/**
 * F_add_element()
 */
bool F_add_element(uint32_t u32_id, uint64_t u64_value)
{
    bool b_rc = false;
    uint32_t u32_index = 0U;
    uint32_t u32_counter = 0U;
    bool b_continue_loop = true;

    if (S_u16_item_count < MAX_ELEMENTS)
    {
        u32_index = F_hash_function(u32_id);

        /* Check if an entry already exists for this ID */
        if (S_st_hash_table[u32_index] == NULL)
        {
            /* Search for a free slot in the main table */
            for (u32_counter = 0U;
                 (u32_counter < MAX_ELEMENTS) && (b_continue_loop == true);
                 u32_counter++)
            {
                if (S_st_table_entry[u32_counter].b_used == false)
                {
                    S_st_table_entry[u32_counter].b_used = true;
                    S_st_table_entry[u32_counter].u32_id = u32_id;
                    S_st_table_entry[u32_counter].u64_value = u64_value;

                    /* Update the hash table */
                    S_st_hash_table[u32_index] = &S_st_table_entry[u32_counter];

                    S_u16_item_count++;
                    b_continue_loop = false;
                    b_rc = true;
                }
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

    if (p_u64_found_value != NULL)
    {
        uint32_t u32_index = F_hash_function(u32_search_id);
        TYP_ELEMENT_ENTRY *p_current = S_st_hash_table[u32_index];

        if ((p_current != NULL) &&
            (p_current->b_used == true) &&
            (p_current->u32_id == u32_search_id))
        {
            *p_u64_found_value = p_current->u64_value;
            b_rc = true;
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
    (void)F_add_element(2000U, 123U);

    uint64_t u64_value = 0U;
    if (F_search_element(1000U, &u64_value))
        printf("ID 1000 -> value = %lu\n", u64_value);
    else
        printf("ID 1000 not found\n");

    uint64_t u64_value2 = 0U;
    if (F_search_element(2000U, &u64_value2))
        printf("ID 2000 -> value = %lu\n", u64_value2);
    else
        printf("ID 2000 not found\n");

    return 0;
}
