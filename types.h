#ifndef __TYPES_H_
#define __TYPES_H_

#include <memory> // c++0x shared_ptr

/*
 * typedefs smart pointer to some of quadris modules
 * for easier typing
 */

class Block;
typedef std::shared_ptr<Block> BlockPtr;

class Xwindow;
typedef std::shared_ptr<Xwindow> XwindowPtr;

class Command;
typedef std::shared_ptr<Command> CommandPtr;

class BlockFactory;
typedef std::shared_ptr<BlockFactory> BlockFactoryPtr;

#endif
