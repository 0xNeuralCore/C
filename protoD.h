#ifndef PROTO_D_H
#define PROTO_D_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_ELEMENTS 1000U
#define HASH_SIZE 100U

/**
 * TODO: Add description
 */
typedef struct STRUCT_ELEMENT_ENTRY
{
    bool b_used;
    uint8_t tu08_ip_src[4];
    uint16_t u16_port_src;
    uint8_t tu08_ip_dst[4];
    uint16_t u16_port_dst;
    uint64_t u64_value;
    struct STRUCT_ELEMENT_ENTRY *p_next;
} TYP_ELEMENT_ENTRY;

/**
 * TODO: Add description
 */
uint32_t F_hash_function(const uint8_t tu08_ip_src[4], uint16_t u16_port_src,
                         const uint8_t tu08_ip_dst[4], uint16_t u16_port_dst);

/**
 * TODO: Add description
 */
bool F_add_element(const uint8_t ip_src[4], uint16_t port_src,
                   const uint8_t ip_dst[4], uint16_t port_dst,
                   uint64_t u64_value);
/**
 * TODO: Add description
 */
bool F_search_element(const uint8_t ip_src[4], uint16_t port_src,
                      const uint8_t ip_dst[4], uint16_t port_dst,
                      uint64_t *p_u64_found_value);

#endif /* PROTO_D_H */
