#pragma once
#include <winsock.h>
#include <string>
using namespace std;
struct Gladiator
{
private:
	SOCKET connection;
	char* type;
	int number;
	int victories = 0;
	int defeats = 0;
	int pid;
public:

	Gladiator()
	{
		number = 0;
		connection = NULL;
		type = NULL;
	}

	Gladiator(SOCKET connection, char* type, int number,int pid)
	{
		this->connection = connection;
		this->type = type;
		this->number = number;
		this->pid = pid;
	}

	Gladiator(const Gladiator& gladiator)
	{
		this->connection = gladiator.connection;
		this->type = gladiator.type;
		this->number = gladiator.number;
		this->pid = gladiator.pid;
	}

	Gladiator& operator = (const Gladiator& gladiator)
	{
		if (this->type != NULL) delete type;
		this->connection = gladiator.connection;
		this->type = gladiator.type;
		this->number = gladiator.number;
		return *this;
	}

	std::string getType()
	{
		return type;
	}

	int getNumber()
	{
		return number;
	}

	int getVictories()
	{
		return victories;
	}

	int getDefeats()
	{
		return defeats;
	}

	int getPID()
	{
		return pid;
	}

	void incVictories()
	{
		++victories;
	}

	void incDefats()
	{
		++defeats;
	}

	std::string toString()
	{
		std::string str;
		str += std::to_string(number) + "\t" + type + "\t" + std::to_string(victories) + "\t" + std::to_string(defeats);
		return str;
	}

	~Gladiator()
	{
		delete type;
	}

};
