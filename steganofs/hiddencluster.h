#ifndef _HIDDENCLUSTER_H_
#define _HIDDENCLUSTER_H_

/**
 * @file hiddencluster.h
 * @brief Header file for hidden cluster operations.
 */

#include <stdbool.h>
#include <stddef.h>

#include "hiddenfat.h"
#include "hiddenfile.h"

/**
 * @struct HiddenFile
 * @brief Represents a hidden file in the hidden FAT filesystem.
 */
typedef struct HiddenFat HiddenFat;

/**
 * @struct HiddenCluster
 * @brief Structure representing a hidden cluster.
 */
typedef struct HiddenCluster HiddenCluster;

/**
 * @struct HiddenFile
 * @brief Represents a hidden file in the hidden FAT filesystem.
 */

typedef struct HiddenFile HiddenFile;

/**
 * @enum State
 * @brief Enumeration representing the state of a hidden cluster.
 */
enum State {
    FREE = 0, /**< Cluster is free. */
    RESERVED = 1, /**< Cluster is reserved. */
    DEFECT = 2, /**< Cluster is defective. */
    ALLOCATED = 3 /**< Cluster is allocated. */
};

/**
 * @struct HiddenCluster
 * @brief Structure representing a hidden cluster.
 */
struct HiddenCluster {
    size_t b_index; /**< Index of the cluster within a block. */
    size_t cluster_index; /**< Index of the cluster within the filesystem. */
    unsigned int state; /**< State of the cluster (enum State). */
    HiddenCluster *prev; /**< Pointer to the previous cluster in the linked list. */
    HiddenCluster *next; /**< Pointer to the next cluster in the linked list. */
    HiddenFile *file; /**< Pointer to the file associated with the cluster. */
};

/**
 * @brief Swaps two hidden clusters within a hidden FAT.
 *
 * This function swaps two hidden clusters within a hidden FAT.
 *
 * @param hidden_fat Pointer to the HiddenFat structure.
 * @param b_index_a Index of the first cluster to be swapped.
 * @param b_index_b Index of the second cluster to be swapped.
 * @return Returns true if the swap is successful, false otherwise.
 */
bool swap_hidden_clusters (HiddenFat *hidden_fat, size_t b_index_a, size_t b_index_b);

/**
 * @brief Extends a hidden cluster for a hidden file.
 *
 * This function extends a hidden cluster for a hidden file in a hidden FAT.
 *
 * @param hidden_fat Pointer to the HiddenFat structure.
 * @param p_file Pointer to the HiddenFile structure.
 * @return Returns true if the extension is successful, false otherwise.
 */
bool extend_hidden_cluster (HiddenFat *hidden_fat, HiddenFile *p_file);

#endif //_HIDDENCLUSTER_H_