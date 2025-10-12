#include "protoA.h"
#include <stdio.h> // nécessaire pour printf dans main()

static TYP_ELEMENT_ENTRY S_st_table_entry[MAX_ITEMS];
static uint16_t S_u16_item_count = 0U;

bool F_add_element(uint32_t u32_id, uint64_t u64_value)
{
    bool b_rc = false;
    uint32_t u32_counter = 0U;
    bool b_continue_loop = true;

    if (S_u16_item_count < MAX_ITEMS)
    {
        /* Recherche d’un emplacement libre */
        for (u32_counter = 0U;
             (u32_counter < MAX_ITEMS) && (b_continue_loop == true);
             u32_counter++)
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

bool F_search_element(uint32_t u32_search_id, uint64_t *p_u64_found_value)
{
    bool b_rc = false;
    uint32_t u32_counter = 0U;
    bool b_continue_loop = true;

    if (p_u64_found_value != NULL)
    {
        for (u32_counter = 0U;
             (u32_counter < MAX_ITEMS) && (b_continue_loop == true);
             u32_counter++)
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

int main(void)
{
    (void)F_add_element(100U, 42U);
    (void)F_add_element(200U, 84U);

    uint64_t value = 0U;
    bool found = F_search_element(200U, &value);

    if (found == true)
    {
        printf("ID 200 -> value = %lu\n", value);
    }
    else
    {
        printf("ID non trouvé\n");
    }

    return 0;
}
