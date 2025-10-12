#ifndef PROTO_B_H
#define PROTO_B_H

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
 * @brief Ajoute un nouvel élément dans la table avec gestion par hachage simple.
 *
 * Cette fonction calcule l’index de hachage, vérifie l’absence de doublon,
 * puis ajoute l’élément dans le tableau statique et met à jour la table
 * de hachage. En cas de collision, le nouvel élément écrase l’ancien.
 *
 * @param[in] u32_id    Identifiant unique de l’élément.
 * @param[in] u64_value Valeur associée à l’élément.
 * @return true si l’ajout a réussi, false sinon (table pleine).
 */
bool F_add_element(uint32_t u32_id, uint64_t u64_value);

/**
 * @brief Recherche un élément par son identifiant dans la table hachée.
 *
 * Cette fonction utilise la table de hachage pour accéder directement
 * à l’entrée correspondante. En cas de collision (même index hash),
 * seul le dernier élément ajouté est visible.
 *
 * @param[in]  u32_search_id      Identifiant recherché.
 * @param[out] p_u64_found_value  Pointeur pour stocker la valeur trouvée.
 * @return true si l’élément est trouvé, false sinon.
 */
bool F_search_element(uint32_t u32_search_id, uint64_t *p_u64_found_value);

#endif /* PROTO_B_H */
