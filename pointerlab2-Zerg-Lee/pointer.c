// DO NOT INCLUDE ANY OTHER LIBRARIES/FILES
#include "pointer.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// In this assignment, you can assume that function parameters are valid and the memory is managed by the caller //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Returns the area of a rectangle
// The shape is guaranteed to be a valid rectangle
double rectangle_area(void* shape)
{
    rectangle_t* rectangle = (rectangle_t*)shape;
    // IMPLEMENT THIS
    return rectangle->length * rectangle->width;
}

// Returns the area of an equilateral triangle
// The shape is guaranteed to be a valid triangle
// The area of an equilateral triangle is sqrt(3)/4 times length squared
double triangle_area(void* shape)
{
    triangle_t* triangle = (triangle_t*)shape;
    // IMPLEMENT THIS
    return sqrt(3) / 4 * pow(triangle->length,2);
}

// Returns the perimeter of a rectangle
// The shape is guaranteed to be a valid rectangle
double rectangle_perimeter(void* shape)
{
    rectangle_t* rectangle = (rectangle_t*)shape;
    // IMPLEMENT THIS
    return (rectangle->length + rectangle->width) * 2;
}

// Returns the perimeter of an equilateral triangle
// The shape is guaranteed to be a valid triangle
double triangle_perimeter(void* shape)
{
    triangle_t* triangle = (triangle_t*)shape;
    // IMPLEMENT THIS
    return triangle->length * 3;
}

// Initializes a rectangle shape
void rectangle_construct(rectangle_t* shape, const char* name, double width, double length)
{
    // IMPLEMENT THIS

    rectangle_t* rectangle = shape;
    rectangle->shape.virtual_func_table.area= *rectangle_area;
    rectangle->shape.virtual_func_table.perimeter = *rectangle_perimeter;
    rectangle->shape.name = name;
    rectangle->shape.edges = 4;
    rectangle->length = length;
    rectangle->width = width;
}

// Initializes a triangle shape
void triangle_construct(triangle_t* shape, const char* name, double length)
{
    // IMPLEMENT THIS
    triangle_t* triangle = shape;
    triangle->shape.virtual_func_table.area = *triangle_area;
    triangle->shape.virtual_func_table.perimeter = *triangle_perimeter;
    triangle->shape.name = name;
    triangle->shape.edges = 3;
    triangle->length = length;
}

// Compares the area of shape1 with shape2
// Returns -1 if the area of shape1 is less than the area of shape2
// Returns 1 if the area of shape1 is greater than the area of shape2
// Returns 0 if the area of shape1 is equal to the area of shape2
int compare_by_area(shape_t* shape1, shape_t* shape2)
{
    // IMPLEMENT THIS
    shape_t* shapes1 = shape1;
    shape_t* shapes2 = shape2;
    if (shapes1->virtual_func_table.area(shapes1) < shapes2->virtual_func_table.area(shapes2))
    {
        return -1;
    }
    if (shapes1->virtual_func_table.area(shapes1) > shapes2->virtual_func_table.area(shapes2))
    {
        return 1;
    }
    if (shapes1->virtual_func_table.area(shapes1) == shapes2->virtual_func_table.area(shapes2))
    {
        return 0;
    }
    return 0;  
}

// Compares the perimeter of shape1 with shape2
// Returns -1 if the perimeter of shape1 is less than the perimeter of shape2
// Returns 1 if the perimeter of shape1 is greater than the perimeter of shape2
// Returns 0 if the perimeter of shape1 is equal to the perimeter of shape2
int compare_by_perimeter(shape_t* shape1, shape_t* shape2)
{
    // IMPLEMENT THIS
    shape_t* shapes1 = shape1;
    shape_t* shapes2 = shape2;
    if (shapes1->virtual_func_table.perimeter(shapes1) < shapes2->virtual_func_table.perimeter(shapes2))
    {
        return -1;
    }
    if (shapes1->virtual_func_table.perimeter(shapes1) > shapes2->virtual_func_table.perimeter(shapes2))
    {
        return 1;
    }
    if (shapes1->virtual_func_table.perimeter(shapes1) == shapes2->virtual_func_table.perimeter(shapes2))
    {
        return 0;
    }
    return 0;
}

//
// Linked list functions
//


//Sort the Linked_list by the given list comparison function 
void linked_list_sort(linked_list_t* list)
{
    linked_list_t* unorder_list = list;
    linked_list_node_t* the_this_one = unorder_list->head;
    linked_list_node_t* the_next_one = the_this_one->next;
    linked_list_node_t* the_last_one = the_next_one->next;
    while (true)
    {

        while (the_next_one != NULL)
        {
            if (unorder_list->compare(the_this_one->shape, the_next_one->shape) == 1)
            {
                the_next_one->next = the_this_one;
                the_this_one = the_next_one;
                the_this_one->next = the_last_one;

            }
            else
            {
                the_next_one = the_next_one->next;
            }
        }
    }
}

// Initializes a singly linked list
// If compare is NULL, the list is unsorted and new nodes are inserted at the head of the list
// If compare is not NULL, the list is sorted in increasing order based on the comparison function
void linked_list_init(linked_list_t* list, compare_fn compare)
{
    // IMPLEMENT THIS
    if (compare == NULL)
    {
        linked_list_t* unsort_list = list;
        unsort_list->compare = NULL;
        unsort_list->head = NULL;
    }
    else
    {
        linked_list_t* sort_list = list;
        sort_list->compare = compare;
        sort_list->head = NULL;
        linked_list_sort(sort_list);
    }
}

// Inserts a node into the linked list based on the list comparison function
void linked_list_insert(linked_list_t* list, linked_list_node_t* node)
{
    // IMPLEMENT THIS
    linked_list_t* the_list = list;
    linked_list_node_t* the_node = node;
    the_node->next = the_list->head;
    the_list->head = node;
    if (the_list->compare != NULL)
    {
        linked_list_sort(the_list);
    }
}

// Removes all nodes from the linked list containing the given shape
void linked_list_remove(linked_list_t* list, shape_t* shape)
{
    // IMPLEMENT THIS
    linked_list_t* the_list = list;
    shape_t* the_shape = shape;    
    linked_list_node_t* the_this_one = the_list->head;
    linked_list_node_t* the_next_one = the_this_one->next;
    while (the_this_one->next != NULL)
    {
        if (the_this_one->shape == shape)
        {
            the_this_one = the_next_one;
        }
        else 
        {
            the_this_one = the_this_one->next;
        }
    }
    if (the_list->compare != NULL)
    {
        linked_list_sort(the_list);
    }
}



//
// Tree iterator functions
//

// Initializes an iterator to the beginning of a tree (i.e., first in-order node)
void tree_iterator_begin(tree_iterator_t* iter, tree_node_t* root)
{
    /*tree_iterator_t* tree = iter;
    tree_node_t* first_root = root;
    tree->curr = root;
    tree->depth = 0;
    tree->parents = NULL;*/
        // IMPLEMENT THIS
}

// Updates an iterator to move to the next in-order node in the tree if possible
// Moving past the last in-order node in the tree results in the iterator reaching a NULL state representing the end of the tree
void tree_iterator_next(tree_iterator_t* iter)
{
    tree_iterator_t* tree = iter;
    if (tree->curr->left != NULL) 
    {
        tree->curr = tree->curr->left;
    }
    else
    {   
        for (int i = 1; i < 30; i++)
        {
            if (tree->parents[i]->right != NULL)
            {
                tree->curr = tree->parents[i]->right;
                break;
            }
        }
    }
}

// Returns true if iterator is at the end of the tree or false otherwise
// The end of the tree is the position after the last in-order node in the tree (i.e., NULL state from tree_iterator_next)
bool tree_iterator_at_end(tree_iterator_t* iter)
{
    /*tree_iterator_t* tree = iter;
    for (int i = 0; i < pow(2,30); i++)
    {
        if (tree->curr->right != NULL)
        {
            tree->curr = tree->curr->right;
        }
        if (tree->curr->right == NULL && tree->curr->left != NULL)
        {
            tree->curr = tree->curr->left;
        }
        if (tree->curr->right == NULL && tree->curr->left == NULL)
        {
            break;
        }

    }
    tree->curr = tree->curr->left;
    if (tree->curr == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }*/
    return false;
}

// Returns the current node that the iterator references or NULL if the iterator is at the end of the tree
tree_node_t* tree_iterator_get_node(tree_iterator_t* iter)
{
    // IMPLEMENT THIS
    //tree_iterator_t* tree = iter;
    //if (tree->curr == tree_iterator_at_end(tree))
    //{
        return NULL;
    //}
    //return tree->curr;
}

// Returns the current shape that the iterator references or NULL if the iterator is at the end of the tree
shape_t* tree_iterator_get_shape(tree_iterator_t* iter)
{
    // IMPLEMENT THIS
  //  tree_iterator_t* tree = iter;
   // if (tree->curr == tree_iterator_at_end(tree))
   // {
        return NULL;
   // }
   // return tree->curr->shape;
}

//
// Tree analysis functions
//

// Returns the maximum, minimum, and average area of shapes in the tree
// An empty tree should not modify the maximum, minimum, or average
void max_min_avg_area(tree_node_t* root, double* max, double* min, double* avg)
{
    // IMPLEMENT THIS
    /*double* loc_max = max;
    double* loc_min = min;
    double* loc_avg = avg;
    double loc_sum = 0;
    int total_num = 1;
    tree_iterator_t* tree = iter;
    for (int i = 1; i < 30; i++)
    {
        if (tree->parents[i] == NULL)
        {
            tree->curr = tree->parents[i];
            break;
        }
    }
    for (int i = 0; i < pow(2, 30); i++)
    {
        if (loc_max < tree->curr->shape)
        {
            loc_max = tree->curr->shape;
        }
        if (loc_min > tree->curr->shape)
        {
            loc_min = tree->curr->shape;
        }
        loc_sum = loc_sum + tree->curr->shape;
        total_num++;
        if (tree->curr->right == NULL && tree->curr->left == NULL)
        {
            break;
        }

    }
    loc_avg = loc_sum / total_num;*/

}

// Executes the func function for each node in the tree in-order
// The function takes in an input data and returns an output data, which is used as input to the next call to the function
// The initial input data is provided as a parameter to foreach, and foreach returns the final output data
// For example, if there are three nodes, foreach should behave like: return func(node3, func(node2, func(node1, data)))
double foreach(tree_node_t* root, foreach_fn func, double data)
{
    // IMPLEMENT THIS
    /*tree_node_t* root_curr = root;
    double data_first = func(root_curr->shape, data);
    for (root_curr->right != NULL && root_curr->left != NULL)
    {
        data_first = func(root_curr->shape, data_first);
        if (root_curr->left != NULL)
        {
            root_curr = root_curr->left;
            foreach(root_curr, func, data_first)
        }
        if (root_curr->right != NULL)
        {
            root_curr = root_curr->right;
            foreach(root_curr, func, data_first)
        }
    }*/
    return 0;
}
