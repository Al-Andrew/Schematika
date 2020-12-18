#include "interpreter.hpp"

void interpret(std::vector<Block> blocks)
{
	Block start = *std::find_if(std::begin(blocks), std::end(blocks), [](Block b) {return b.type == Type::START; });
	Node* st = start.nodes[0];
	std::ofstream fout("run.py");
	
	while (true)
	{
		while (st->next != nullptr)
			st = st->next;

		if (st->host != nullptr and st->host->type == Type::INPUT)
		{
			std::string var = st->host->text;
			fout << var << " = float(input(\"" << var << ": \"))\n";
			st = st->host->nodes[0];
		}
		else if (st->host != nullptr and st->host->type == Type::CALCUL)
		{
			std::string var = st->host->text;
			fout << var << "\n";
			st = st->host->nodes[0];
		}
		else if (st->host != nullptr and st->host->type == Type::OUTPUT)
		{
			std::string var = st->host->text;
			fout <<"print("<< var <<")\n";
			st = st->host->nodes[0];
		}

		else if (st->host != nullptr and st->host->type == Type::STOP)
			break;
	}
	fout.close();
	system("cls");
	system("python run.py");
}