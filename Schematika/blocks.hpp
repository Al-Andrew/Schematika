#pragma once
#include "sl.h"
#include <string>
#include <vector>
#include <cstdint>

/// <summary>
/// Enum to hold all the types of blocks
/// </summary>
/// <author>Andrei</author>
enum class Type
{
    START,
    STOP,
    INPUT,
    OUTPUT,
    CALCUL,
    DECIZIE,
    NOT_A_BLOCK
};

/// <summary>
/// Vector containing all types for easy iteration
/// </summary>
/// <author>Andrei</author>
const std::vector<Type> allTypes = { Type::START,Type::STOP,Type::INPUT,Type::OUTPUT,Type::CALCUL,Type::DECIZIE };

/// Forward declarations of both structs so they can be included in one-another
struct Block;
struct Node;

/// <summary>
/// A node struct to link up the blocks
/// </summary>
/// <author>Andrei</author>
/// <author>Cristi</author>
struct Node
{
    double x = 0, y = 0, r = 0;
    float floating = false;
    Node* next = nullptr;
    Block* host = nullptr;
};

/// <summary>
/// The main struct for data
/// </summary>
/// <author>Andrei</author>
/// <author>Cristi</author>
struct Block {
    Type type = Type::START;
    double x = 0, y = 0;
    double width = 0, height = 0;
    bool floating = false;
    std::vector<Node* > nodes;
};

/// <summary>
/// Generic functions that call the specialized ones
/// </summary>
/// <param name="b"> A block to operate on</param>
/// <author>Andrei</author>
void draw(const Block& b);

/// <summary>
/// Updates the given block taking in account the cooldown for clicks
/// </summary>
/// <param name="b">block to be updated</param>
/// <param name="cooldown">current click cooldown</param>
/// <author>Andrei</author>
void update(Block& b, double& cooldown);

/// <summary>
/// Specialized functions to draw all types of blocks
/// </summary>
/// <param name="b"></param>
/// <author>Andrei</author>
/// <author>Cristi</author>
void drawStart(const Block& b);
void drawStop(const Block& b);
void drawCalcul(const Block& b);
void drawDecizie(const Block& b);
void drawInput(const Block& b);
void drawOutput(const Block& b);


/// <summary>
/// Universal generator
/// </summary>
/// <param name="t">The tyep of block to be constructed</param>
/// <returns>A constructed block of type t</returns>
Block generate(Type t);

/// <summary>
/// Generators for all types of blocks
/// </summary>
/// <returns>The generated blocks with the right attributes set</returns>
/// <author>Andrei</author>
/// <author>Cristi</author>
Block generateStart();
Block generateStop();
Block generateCalcul();
Block generateDecizie();
Block generateInput();
Block generateOutput();


void drawNode(Node* n);
void updateNode(Node*& n, std::vector<Node*>& nodes, double& cooldown);