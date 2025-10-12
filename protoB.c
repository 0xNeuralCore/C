#include "protoB.h"
#include <stdio.h> /* pour printf */

static TYP_ELEMENT_ENTRY S_st_table_entry[MAX_ITEMS];
static TYP_ELEMENT_ENTRY *S_st_hash_table[MAX_ITEMS] = {0};
static uint16_t S_u16_item_count = 0U;

/**
 * @brief Fonction de hachage simple : modulo MAX_ITEMS.
 * @param u32_key Clé/id à hacher.
 * @return Index dans la table de hachage.
 */
static uint32_t F_hash_function(uint32_t u32_key);

/**
 * F_hash_function()
 */
static uint32_t F_hash_function(uint32_t u32_key)
{
    return u32_key % MAX_ITEMS; /* ✅ Enlever le +1U */
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

    if (S_u16_item_count < MAX_ITEMS)
    {
        u32_index = F_hash_function(u32_id);

        /* Vérifie si une entrée existe déjà pour cet ID */
        if (S_st_hash_table[u32_index] == NULL)
        {
            /* Recherche d'une case libre dans la table principale */
            for (u32_counter = 0U;
                 (u32_counter < MAX_ITEMS) && (b_continue_loop == true);
                 u32_counter++)
            {
                if (S_st_table_entry[u32_counter].b_used == false)
                {
                    S_st_table_entry[u32_counter].b_used = true;
                    S_st_table_entry[u32_counter].u32_id = u32_id;
                    S_st_table_entry[u32_counter].u64_value = u64_value;

                    /* Mise à jour de la table de hachage */
                    S_st_hash_table[u32_index] = &S_st_table_entry[u32_counter];

                    S_u16_item_count++;
                    b_continue_loop = false;
                    b_rc = true;
                }
            }
        }
        else
        {
            /* Collision : pas gérée dans ce prototype */
            b_rc = false;
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
    (void)F_add_element(100U, 84U);
    (void)F_add_element(200U, 99U);

    uint64_t u64_value = 0U;
    bool b_found = F_search_element(100U, &u64_value);

    if (b_found == true)
    {
        printf("ID 100 -> value = %lu\n", u64_value);
    }
    else
    {
        printf("ID non trouvé\n");
    }

    uint64_t u64_value_2 = 0U;
    bool b_found_2 = F_search_element(200U, &u64_value_2);

    if (b_found_2 == true)
    {
        printf("ID 200 -> value = %lu\n", u64_value_2);
    }
    else
    {
        printf("ID non trouvé\n");
    }

    return 0;
}
