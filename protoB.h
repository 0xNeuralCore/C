#ifndef PROTO_B_H
#define PROTO_B_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_ELEMENTS 1000U

/**
 * @brief Table element structure
 * @param b_used    Usage flag
 * @param u32_id    Unique identifier
 * @param u64_value Associated value
 */
typedef struct STRUCT_ELEMENT_ENTRY
{
    bool b_used;
    uint32_t u32_id;
    uint64_t u64_value;
} TYP_ELEMENT_ENTRY;

/**
 * @brief Adds a new element to the table
 * @param u32_id    Element unique identifier
 * @param u64_value Element value
 * @return true if successful, false if table is full
 */
bool F_add_element(uint32_t u32_id, uint64_t u64_value);

/**
 * @brief Searches for an element by its ID
 * @param u32_search_id     ID to search for
 * @param p_u64_found_value Pointer to store found value
 * @return true if found, false otherwise
 */
bool F_search_element(uint32_t u32_search_id, uint64_t *p_u64_found_value);

#endif /* PROTO_B_H */
