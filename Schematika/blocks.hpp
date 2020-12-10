#pragma once
#include "sl.h"
#include <string>
#include<vector>

enum Type
{
	START,
	STOP,
	CALCUL,
	DECIZIE,
	INPUT,
	OUTPUT
};


struct Block;
struct Node;

/** \brief A node to link up the blocks
 * @Andrei @Cristi
 */
struct Node
{
	int x, y, r;
	Node* next;
	Block* host;
};

/** \brief The main struct of data
 * @Andrei @Cristi
 */
struct Block{
	Type type;
	int x, y;
	int width, height;
	bool floating;
	std::vector<Node* > nodes;
};

/// <summary>
/// Generic functions that call the specialized onc
/// </summary>
/// <param name="b"> A block to operate on</param>
/// @Andrei
void draw(const Block& b);
void update(Block& b, double& cooldown);

/// <summary>
/// Specialized functions to draw all types of blocks
/// </summary>
/// <param name="b"></param>
/// @Andrei @Cristi
void drawStart(const Block& b);
void drawStop(const Block& b);
void drawCalcul(const Block& b);
void drawDecizie(const Block& b);
void drawInput(const Block& b);
void drawOutput(const Block& b);


Block generateStart();
Block generateStop();
Block generateCalcul();
Block generateDecizie();
Block generateInput();
Block generateOutput();
