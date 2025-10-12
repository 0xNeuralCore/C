#include "protoB.h"
#include <stdio.h> // pour printf

#define HASH_SIZE 100U // Nombre premier pour la table de hachage

static TYP_ELEMENT_ENTRY S_st_table_entry[MAX_ITEMS];
static TYP_ELEMENT_ENTRY *S_st_hash_table[HASH_SIZE] = {0};
static uint16_t S_u16_item_count = 0U;

/**
 * @brief Fonction de hachage simple : modulo HASH_SIZE.
 * @param u32_key Clé/id à hacher.
 * @return Index dans la table de hachage.
 */
static uint32_t F_hash_function(uint32_t u32_key)
{
    return u32_key % HASH_SIZE;
}

/**
 * @brief Ajoute un nouvel élément dans la table avec gestion par hachage.
 *
 * Cette fonction calcule l’index de hachage, vérifie l’absence de doublon,
 * puis ajoute l’élément dans le tableau statique et dans la table de hachage
 * en tête de liste chaînée.
 *
 * @param[in] u32_id    Identifiant unique de l’élément.
 * @param[in] u64_value Valeur associée à l’élément.
 * @return true si l’ajout a réussi, false sinon (doublon ou table pleine).
 */
bool F_add_element(uint32_t u32_id, uint64_t u64_value)
{
    bool b_rc = false;
    uint32_t u32_index = 0U;

    if (S_u16_item_count >= MAX_ITEMS)
    {
        /* Table pleine : ajout impossible */
        return false;
    }

    u32_index = F_hash_function(u32_id);

    /* Vérification doublon dans la liste chaînée */
    TYP_ELEMENT_ENTRY *p_current = S_st_hash_table[u32_index];
    while (p_current != NULL)
    {
        if ((p_current->b_used == true) && (p_current->u32_id == u32_id))
        {
            /* Doublon trouvé : ajout refusé */
            return false;
        }
        p_current = p_current->p_next;
    }

    /* Recherche d’une case libre dans le tableau statique */
    for (uint32_t u32_counter = 0U; u32_counter < MAX_ITEMS; u32_counter++)
    {
        if (S_st_table_entry[u32_counter].b_used == false)
        {
            S_st_table_entry[u32_counter].b_used = true;
            S_st_table_entry[u32_counter].u32_id = u32_id;
            S_st_table_entry[u32_counter].u64_value = u64_value;

            /* Insertion en tête de la liste de hachage */
            S_st_table_entry[u32_counter].p_next = S_st_hash_table[u32_index];
            S_st_hash_table[u32_index] = &S_st_table_entry[u32_counter];

            S_u16_item_count++;
            b_rc = true;
            break;
        }
    }

    return b_rc;
}

/**
 * @brief Recherche un élément par son identifiant dans la table hachée.
 *
 * Parcourt la liste chaînée de l’index calculé par la fonction de hachage.
 * Si l’élément est trouvé, copie la valeur dans la variable pointée.
 *
 * @param[in]  u32_search_id      Identifiant recherché.
 * @param[out] p_u64_found_value  Pointeur pour stocker la valeur trouvée.
 * @return true si l’élément est trouvé, false sinon.
 */
bool F_search_element(uint32_t u32_search_id, uint64_t *p_u64_found_value)
{
    bool b_rc = false;

    if (p_u64_found_value != NULL)
    {
        uint32_t u32_index = F_hash_function(u32_search_id);
        TYP_ELEMENT_ENTRY *p_current = S_st_hash_table[u32_index];

        while (p_current != NULL)
        {
            if ((p_current->b_used == true) && (p_current->u32_id == u32_search_id))
            {
                *p_u64_found_value = p_current->u64_value;
                b_rc = true;
                break;
            }
            p_current = p_current->p_next;
        }
    }

    return b_rc;
}

int main(void)
{
    (void)F_add_element(100U, 42U);
    (void)F_add_element(200U, 84U);

    uint64_t u64_value = 0U;
    bool b_found = F_search_element(200U, &u64_value);

    if (b_found == true)
    {
        printf("ID 200 -> value = %lu\n", u64_value);
    }
    else
    {
        printf("ID non trouvé\n");
    }

    return 0;
}
