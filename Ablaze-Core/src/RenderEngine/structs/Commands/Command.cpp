#include "Command.h"

namespace Ablaze
{

	Command::Command(const CommandType& type)
		: type(type)
	{
		
	}

	const CommandType& Command::GetType() const
	{
		return type;
	}

	String Command::ToString() const
	{
		// TODO: replace with type name
		return "Command";
	}

}