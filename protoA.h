#ifndef PROTOA_H
#define PROTOA_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_ITEMS 1000U

typedef struct STRUCT_ELEMENT_ENTRY
{
    bool b_used;
    uint32_t u32_id;
    uint64_t u64_value;
} TYP_ELEMENT_ENTRY;

/**
 * @brief Ajoute un nouvel élément dans le tableau d’entrées.
 *
 * @param[in]  u32_id      Identifiant unique de l’élément à ajouter.
 * @param[in]  u64_value   Valeur associée à l’élément.
 *
 * @return true  si l’ajout a été effectué avec succès.
 * @return false si le tableau est plein ou si aucune case libre n’a été trouvée.
 */
bool F_add_element(uint32_t u32_id, uint64_t u64_value);

/**
 * @brief Recherche un élément dans le tableau à partir de son identifiant.
 *
 * @param[in]   u32_search_id       Identifiant de l’élément à rechercher.
 * @param[out]  p_u64_found_value   Pointeur vers une variable où la valeur trouvée sera stockée.
 *
 * @return true  si l’élément a été trouvé et que la valeur a été copiée.
 * @return false si l’élément n’existe pas ou si le pointeur fourni est nul.
 */
bool F_search_element(uint32_t u32_search_id, uint64_t *p_u64_found_value);

#endif /* PROTOA_H */
