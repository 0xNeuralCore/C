#ifndef PROTO_B_H
#define PROTO_B_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_ITEMS 1000U

/**
 * @brief Structure représentant un élément stocké dans la table.
 */
typedef struct STRUCT_ELEMENT_ENTRY
{
    bool b_used;                         /**< Indique si l’entrée est utilisée. */
    uint32_t u32_id;                     /**< Identifiant unique de l’élément. */
    uint64_t u64_value;                  /**< Valeur associée à l’élément. */
    struct STRUCT_ELEMENT_ENTRY *p_next; /**< Pointeur vers l’entrée suivante en cas de collision. */
} TYP_ELEMENT_ENTRY;

/**
 * @brief Ajoute un nouvel élément dans la table avec gestion par hachage.
 *
 * @param[in]  u32_id      Identifiant unique de l’élément.
 * @param[in]  u64_value   Valeur associée à l’élément.
 *
 * @return true si l’ajout a été effectué avec succès.
 * @return false si la table est pleine ou si l’identifiant existe déjà.
 */
bool F_add_element(uint32_t u32_id, uint64_t u64_value);

/**
 * @brief Recherche un élément dans la table à partir de son identifiant.
 *
 * @param[in]   u32_search_id       Identifiant de l’élément à rechercher.
 * @param[out]  p_u64_found_value   Pointeur pour stocker la valeur trouvée.
 *
 * @return true si l’élément est trouvé, false sinon.
 */
bool F_search_element(uint32_t u32_search_id, uint64_t *p_u64_found_value);

#endif /* PROTO_B_H */
