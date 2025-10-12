#include "protoA.h"
#include <stdio.h> /* pour printf */

static TYP_ELEMENT_ENTRY S_st_table_entry[MAX_ITEMS];
static uint16_t S_u16_item_count = 0U;

/**
 * F_add_element()
 */
bool F_add_element(uint32_t u32_id, uint64_t u64_value)
{
    bool b_rc = false;
    uint32_t u32_counter = 0U;
    bool b_continue_loop = true;

    if (S_u16_item_count < MAX_ITEMS)
    {
        /* Recherche d’un emplacement libre */
        for (u32_counter = 0U; (u32_counter < MAX_ITEMS) && b_continue_loop; u32_counter++)
        {
            if (S_st_table_entry[u32_counter].b_used == false)
            {
                S_st_table_entry[u32_counter].b_used = true;
                S_st_table_entry[u32_counter].u32_id = u32_id;
                S_st_table_entry[u32_counter].u64_value = u64_value;

                S_u16_item_count++;
                b_continue_loop = false;
                b_rc = true;
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
    uint32_t u32_counter = 0U;
    bool b_continue_loop = true;

    if (p_u64_found_value != NULL)
    {
        for (u32_counter = 0U; (u32_counter < MAX_ITEMS) && b_continue_loop; u32_counter++)
        {
            if ((S_st_table_entry[u32_counter].b_used == true) &&
                (S_st_table_entry[u32_counter].u32_id == u32_search_id))
            {
                *p_u64_found_value = S_st_table_entry[u32_counter].u64_value;
                b_rc = true;
                b_continue_loop = false;
            }
        }
    }

    return b_rc;
}

/**
 * main()
 */
int main(void)
{
    (void)F_add_element(100U, 42U);

    uint64_t u64_value = 0U;
    bool b_found = F_search_element(100U, &u64_value);
    if (b_found == true)
    {
        printf("ID 100U -> value = %lu\n", b_found);
    }
    else
    {
        printf("ID non trouvé\n");
    }

    return 0;
}
