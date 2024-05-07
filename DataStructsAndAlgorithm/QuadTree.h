#ifndef QUADTREE_H
#define QUADTREE_H

typedef struct quad_tree_entity
{
    void* object;
} QuadTreeEntity;

typedef struct quad_tree_node
{
    QuadTreeEntity* entities;

} QuadTreeNode;

typedef struct quad_tree
{
    QuadTreeNode* root;
    unsigned char maxDepth;
    unsigned char maxSize;
} QuadTree;




#endif // QUADTREE_H
