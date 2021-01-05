#include "interpreter.hpp"
#include <map>
#include <stack>
#include <queue>


bool isnum(std::string var)
{
	for (auto ch : var)
		if (!(isdigit(ch) or ch == '.'))
			return false;
	return true;
}

double var_eval(std::map<std::string, double>& mem, std::string var)
{
	if (isnum(var))
		return std::stod(var);
	else
		return mem[var];
}

void input(std::map<std::string, double>& mem, std::string var)
{
	double a;
	std::cout << "Please input a value for " << var << ": ";
	std::cin >> a;
	mem[var] = a;
}

void output(std::map<std::string, double>& mem, std::string var)
{
	auto search = mem.find(var);
	if (search != mem.end())
	{
		std::cout << var << ": " << mem[var] << std::endl;
	}
	else if (isnum(var))
	{
		std::cout << std::stod(var) << std::endl;
	}
	else if (var[0] == '#')
	{
		std::cout << std::string(var.begin() + 1, var.end() - 1) << std::endl;
	}
	else
	{
		std::cerr << "Error Output: Variable: " << var << " not present in memory. \n";
	}
}


struct op
{
	std::string val;
	int prio;
};


const std::vector<op> all_operators = {
	{"+", 4},
	{"-", 4},
	{"*", 5},
	{"/", 5},
	{"%", 5},
	{"(", 0},
	{")", 0},
	{"**", 6},
	{"&&", -1},
	{"||", -1},
	{"==", -1},
	{">", -1},
	{">=", -1},
	{"<", -1},
	{"<=", -1},
	{"!=", -1}
};




double eval(std::map < std::string, double>& mem, std::vector<std::string>& tokens)
{
	
	//Transform the expresion into polish notation
	std::vector<std::string> polish;
	std::stack<op> operators;

	for (int i = 2; i < tokens.size(); i++)
	{
		auto search1 = std::find_if(std::begin(all_operators), std::end(all_operators), [&](op a) {return a.val == tokens[i]; });
		if (search1 != all_operators.end())
		{
			if (tokens[i] == "(")
				operators.push({ "(",0 });
			else if (tokens[i] == ")")
			{
				op p = operators.top();
				while (p.val != "(")
				{
					polish.push_back(p.val);
					operators.pop();
					p = operators.top();
				}
				operators.pop(); // delete the  "("
			}
			else
			{
				while (!operators.empty() && operators.top().prio >= search1->prio)
				{
					polish.push_back(operators.top().val);
					operators.pop();
				}
				operators.push(*search1);
			}


			continue;
		}
		auto search2 = mem.find(tokens[i]);
		if (search2 != mem.end())
		{
			polish.push_back(tokens[i]);
		}
		else if (isnum(tokens[i]))
			polish.push_back(tokens[i]);
		else if ( tokens[i] != "")
		{
			std::cerr << "Error Eval: Variable: " << tokens[i] << " not present in memory. \n";
		}
		if (polish.back() == "")polish.pop_back();
	}
	while (!operators.empty())
	{
		polish.push_back(operators.top().val);
		operators.pop();
	}
	
	//Now evaluate the expression
	std::reverse(std::begin(polish), std::end(polish));
	for (int i = polish.size() - 1; i >= 0; i--)
	{
		auto search = std::find_if(std::begin(all_operators), std::end(all_operators), [&](op a) {return a.val == polish[i]; });
		if (search != all_operators.end())
		{
			if (polish[i] == "+")
			{
				double a = var_eval(mem, polish[i + 1]);
				double b = var_eval(mem, polish[i + 2]);
				polish.pop_back();
				polish.pop_back();
				polish.pop_back();
				polish.push_back(std::to_string(a + b));
			}
			else if (polish[i] == "-")
			{
				double a = var_eval(mem, polish[i + 1]);
				double b = var_eval(mem, polish[i + 2]);
				polish.pop_back();
				polish.pop_back();
				polish.pop_back();
				polish.push_back(std::to_string(b - a));
			}
			else if (polish[i] == "*")
			{
				double a = var_eval(mem, polish[i + 1]);
				double b = var_eval(mem, polish[i + 2]);
				polish.pop_back();
				polish.pop_back();
				polish.pop_back();
				polish.push_back(std::to_string(b * a));
			}
			else if (polish[i] == "/")
			{
				double a = var_eval(mem, polish[i + 1]);
				double b = var_eval(mem, polish[i + 2]);
				polish.pop_back();
				polish.pop_back();
				polish.pop_back();
				polish.push_back(std::to_string(b / a));
			}
			else if (polish[i] == "%")
			{
				double a = var_eval(mem, polish[i + 1]);
				double b = var_eval(mem, polish[i + 2]);
				polish.pop_back();
				polish.pop_back();
				polish.pop_back();
				polish.push_back(std::to_string(std::fmod(b,a)));
			}
			else if (polish[i] == "**")
			{
				double a = var_eval(mem, polish[i + 1]);
				double b = var_eval(mem, polish[i + 2]);
				polish.pop_back();
				polish.pop_back();
				polish.pop_back();
				polish.push_back(std::to_string(std::pow(b,a)));
			}
			else if (polish[i] == "==")
			{
				double a = var_eval(mem, polish[i + 1]);
				double b = var_eval(mem, polish[i + 2]);
				polish.pop_back();
				polish.pop_back();
				polish.pop_back();
				polish.push_back(std::to_string(a == b));
			}
			else if (polish[i] == "!=")
			{
				double a = var_eval(mem, polish[i + 1]);
				double b = var_eval(mem, polish[i + 2]);
				polish.pop_back();
				polish.pop_back();
				polish.pop_back();
				polish.push_back(std::to_string(a != b));
			}
			else if (polish[i] == "&&")
			{
				double a = var_eval(mem, polish[i + 1]);
				double b = var_eval(mem, polish[i + 2]);
				polish.pop_back();
				polish.pop_back();
				polish.pop_back();
				polish.push_back(std::to_string(b && a));
			}
			else if (polish[i] == "||")
			{
				double a = var_eval(mem, polish[i + 1]);
				double b = var_eval(mem, polish[i + 2]);
				polish.pop_back();
				polish.pop_back();
				polish.pop_back();
				polish.push_back(std::to_string(b || a));
			}
			else if (polish[i] == ">")
			{
				double a = var_eval(mem, polish[i + 1]);
				double b = var_eval(mem, polish[i + 2]);
				polish.pop_back();
				polish.pop_back();
				polish.pop_back();
				polish.push_back(std::to_string(b > a));
			}
			else if (polish[i] == ">=")
			{
				double a = var_eval(mem, polish[i + 1]);
				double b = var_eval(mem, polish[i + 2]);
				polish.pop_back();
				polish.pop_back();
				polish.pop_back();
				polish.push_back(std::to_string(b >= a));
			}
			else if (polish[i] == "<")
			{
				double a = var_eval(mem, polish[i + 1]);
				double b = var_eval(mem, polish[i + 2]);
				polish.pop_back();
				polish.pop_back();
				polish.pop_back();
				polish.push_back(std::to_string(b < a));
			}
			else if (polish[i] == "<=")
			{
			double a = var_eval(mem, polish[i + 1]);
			double b = var_eval(mem, polish[i + 2]);
			polish.pop_back();
			polish.pop_back();
			polish.pop_back();
			polish.push_back(std::to_string(b <= a));
			}

		}
	}

	return std::stod(polish[0]);
}


void calcul(std::map<std::string,double>& mem, std::string& var)
{
	std::vector<std::string> tokens;
	std::stringstream l(var);

	for (std::string tok; std::getline(l, tok, ' '); tokens.emplace_back(tok)); //Split the line into tokens
	{
		auto search = mem.find(tokens[0]);
		if (search == mem.end())
			mem[tokens[0]] = 0;
	}
	mem[tokens[0]] = eval(mem, tokens);

}


void interpret(std::vector<Block> blocks)
{
	Block start = *std::find_if(std::begin(blocks), std::end(blocks), [](Block b) {return b.type == Type::START; });
	Node* st = start.nodes[0];
	std::map<std::string, double> memory;
	
	while (true)
	{
		while (st->next != nullptr)
			st = st->next;

		if (st->host != nullptr and st->host->type == Type::INPUT)
		{
			std::string var = st->host->text;
			input(memory, var);

			st = st->host->nodes[1];
		}
		else if (st->host != nullptr and st->host->type == Type::CALCUL)
		{
			std::string var = st->host->text;
			calcul(memory, var);

			st = st->host->nodes[1];
		}
		else if (st->host != nullptr and st->host->type == Type::OUTPUT)
		{
			std::string var = st->host->text;
			output(memory, var);
			st = st->host->nodes[1];
		}
		else if (st->host != nullptr and st->host->type == Type::DECIZIE)
		{
			std::string var = st->host->text;
			
			std::vector<std::string> tokens{"fill","fill"};
			std::stringstream l(var);
			for (std::string tok; std::getline(l, tok, ' '); tokens.emplace_back(tok)); //Split the line into tokens

			if (eval(memory, tokens) != 0)
				st = st->host->nodes[0];
			else
				st = st->host->nodes[1];
		}

		else if (st->host != nullptr and st->host->type == Type::STOP)
			break;
	}
	std::cout << "Program finished succesfully" << std::endl;
}