#include "interpreter.hpp"
#include <map>
#include <stack>
#include <queue>
#include <algorithm>

bool isnum(std::string var)
{
    for (auto ch : var)
        if (!(isdigit(ch) or ch == '.' or ch == '-'))
            return false;
    return true;
}

std::string string_find_replace(std::string subject, const std::string& search,
    const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
    return subject;
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
    rtrim(var);
    string_find_replace(var, "\n", std::string('\n',1));
    if (var[0] == '#')
    {
        std::cout << std::string(var.begin() + 1, var.begin() + var.find("#", 1)) << std::endl;
    }
    else if (mem.find(var) != mem.end())
    {
        std::cout << var << ": " << mem[var] << std::endl;
    }
    else if (isnum(var))
    {
        std::cout << std::stod(var) << std::endl;
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
    
    //for (auto t : polish)
    //	std::cout << t << " ";
    //std::cout << std::endl;

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
                polish.erase(std::begin(polish) + i + 1, std::begin(polish) + i + 3);
                polish[i] = std::to_string(b + a);
            }
            else if (polish[i] == "-")
            {
                double a = var_eval(mem, polish[i + 1]);
                double b = var_eval(mem, polish[i + 2]);
                polish.erase(std::begin(polish) + i + 1, std::begin(polish) + i + 3);
                polish[i] = std::to_string(b - a);
            }
            else if (polish[i] == "*")
            {
                double a = var_eval(mem, polish[i + 1]);
                double b = var_eval(mem, polish[i + 2]);
                polish.erase(std::begin(polish) + i + 1, std::begin(polish) + i + 3);
                polish[i] = std::to_string(b * a);
            }
            else if (polish[i] == "/")
            {
                double a = var_eval(mem, polish[i + 1]);
                double b = var_eval(mem, polish[i + 2]);
                polish.erase(std::begin(polish) + i + 1, std::begin(polish) + i + 3);
                polish[i] = std::to_string(b / a);
            }
            else if (polish[i] == "%")
            {
                double a = var_eval(mem, polish[i + 1]);
                double b = var_eval(mem, polish[i + 2]);
                polish.erase(std::begin(polish) + i + 1, std::begin(polish) + i + 3);
                polish[i] = std::to_string(std::fmod(b,a));
            }
            else if (polish[i] == "**")
            {
                double a = var_eval(mem, polish[i + 1]);
                double b = var_eval(mem, polish[i + 2]);
                polish.erase(std::begin(polish) + i + 1, std::begin(polish) + i + 3);
                polish[i] = std::to_string(std::pow(b,a));
            }
            else if (polish[i] == "==")
            {
                double a = var_eval(mem, polish[i + 1]);
                double b = var_eval(mem, polish[i + 2]);
                polish.erase(std::begin(polish) + i + 1, std::begin(polish) + i + 3);
                polish[i] = std::to_string(b == a);
            }
            else if (polish[i] == "!=")
            {
                double a = var_eval(mem, polish[i + 1]);
                double b = var_eval(mem, polish[i + 2]);
                polish.erase(std::begin(polish) + i + 1, std::begin(polish) + i + 3);
                polish[i] = std::to_string(b != a);
            }
            else if (polish[i] == "&&")
            {
                double a = var_eval(mem, polish[i + 1]);
                double b = var_eval(mem, polish[i + 2]);
                polish.erase(std::begin(polish) + i + 1, std::begin(polish) + i + 3);
                polish[i] = std::to_string(b && a);
            }
            else if (polish[i] == "||")
            {
                double a = var_eval(mem, polish[i + 1]);
                double b = var_eval(mem, polish[i + 2]);
                polish.erase(std::begin(polish) + i + 1, std::begin(polish) + i + 3);
                polish[i] = std::to_string(b || a);
            }
            else if (polish[i] == ">")
            {
                double a = var_eval(mem, polish[i + 1]);
                double b = var_eval(mem, polish[i + 2]);
                polish.erase(std::begin(polish) + i + 1, std::begin(polish) + i + 3);
                polish[i] = std::to_string(b > a);
            }
            else if (polish[i] == ">=")
            {
                double a = var_eval(mem, polish[i + 1]);
                double b = var_eval(mem, polish[i + 2]);
                polish.erase(std::begin(polish) + i + 1, std::begin(polish) + i + 3);
                polish[i] = std::to_string(b >= a);
            }
            else if (polish[i] == "<")
            {
                double a = var_eval(mem, polish[i + 1]);
                double b = var_eval(mem, polish[i + 2]);
                polish.erase(std::begin(polish) + i + 1, std::begin(polish) + i + 3);
                polish[i] = std::to_string(b < a);
            }
            else if (polish[i] == "<=")
            {
                double a = var_eval(mem, polish[i + 1]);
                double b = var_eval(mem, polish[i + 2]);
                polish.erase(std::begin(polish) + i + 1, std::begin(polish) + i + 3);
                polish[i] = std::to_string(b <= a);
            }
            /*for (auto t : polish)
                std::cout << t << " ";
            std::cout << std::endl;*/
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
    /*for (auto e : memory)
        std::cout << e.first << "=" << e.second << std::endl;*/

    std::cout << "Program finished succesfully" << std::endl;
}


enum TWB
{
    FALS = 0,
    ADEV = 1,
    GATA = 2,
};

std::string translate_exp(std::string exp)
{
    std::string cexp;

    std::vector<std::string> tokens;
    std::stringstream l(exp);

    for (std::string tok; std::getline(l, tok, ' '); tokens.emplace_back(tok));

    for (int i = 0; i < tokens.size(); i++)
    {
        if (tokens[i] == "%")
        {
            tokens[i - 1] = "std::fmod(" + tokens[i - 1] + ", " + tokens[i + 1] + ")";
            tokens.erase(std::begin(tokens) + i, std::begin(tokens) + i + 2);
            i--;
        }
        else if (tokens[i] == "**")
        {
            tokens[i - 1] = "std::pow(" + tokens[i - 1] + ", " + tokens[i + 1] + ")";
            tokens.erase(std::begin(tokens) + i, std::begin(tokens) + i + 2);
            i--;
        }
    }

    for (auto& t : tokens)
        cexp += t;
    return cexp;
}


std::string translate(std::vector<Block> blocks)
{
    Block start = *std::find_if(std::begin(blocks), std::end(blocks), [](Block b) {return b.type == Type::START; });
    Node* st = start.nodes[0];

    std::string code;
    code.reserve(1024);
    code =
        "#include <iostream>\n"
        "#include <cmath>\n"
        "\n"
        "int main()\n"
        "{\n";
    std::map<std::string, int> variables;

    std::stack<Block*> ifs;
    std::map<Block*, std::pair<TWB, std::string>> record; // 
    unsigned int ifcount = 1;

    while (true)
    {
        while (st->next != nullptr)
            st = st->next;

        if (st->host != nullptr and st->host->type == Type::INPUT)
        {
            std::string var = st->host->text;
            if (!(variables[var] == 1))
            {
                code.append("double " + var + ";\n");
                variables[var] = 1;
            }
            code.append("std::cin >> " + var + ";\n");

            st = st->host->nodes[1];
        }
        else if (st->host != nullptr and st->host->type == Type::CALCUL)
        {
            std::string var = st->host->text;
            std::string v = std::string(std::begin(var), var.begin() + var.find(" ", 1));
            if (!(variables[v] == 1))
            {
                code.append("double " + v + ";\n");
              //  std::cout << v << std::endl;
                variables[v] = 1;
            }
            code.append(translate_exp(var) + ";\n");
            st = st->host->nodes[1];
        }
        else if (st->host != nullptr and st->host->type == Type::OUTPUT)
        {
            std::string var = st->host->text;
            rtrim(var);
            if (var[0] == '#')
            {
                code.append("std::cout << \"" + std::string(var.begin() + 1, var.begin() + var.find("#", 1)) + "\";\n");
            }
            else if (variables[var] == 1)
            {
                code.append("std::cout << " + var + ";\n");
            }
            else if (isnum(var))
            {
                code.append("std::cout << " + var + ";\n");
            }
            else
            {
                std::cerr << "Error Output: Variable: " << var << " not present in memory. \n";
            }
          //  std::cout << var << "|"<< std::endl;
            
            st = st->host->nodes[1];
        }
        else if (st->host != nullptr and st->host->type == Type::DECIZIE)
        {
            std::string var = st->host->text;
            var = translate_exp(var);
            if (stack_find(ifs, st->host) == false) //first time seeing a block
            {
                ifs.push(st->host);
                std::string label = "decizie" + std::to_string(ifcount++) + ":\n";
                record[st->host] = std::make_pair<TWB, std::string>(TWB::ADEV, std::string(std::begin(label),std::end(label)-2)); 
                code.append(label);
                code.append("if( " + var + ")\n{\n");
                st = st->host->nodes[0];
            }
            else if (stack_find(ifs, st->host) == true)
            {
                std::string label = record[st->host].second + ";\n}\n";
                code.append("goto " + label);
                code.append("else\n{\n");
                record[st->host].first = TWB::FALS;
                st = st->host->nodes[1];
            }
        }

        else if (st->host != nullptr and st->host->type == Type::STOP)
        {
            if (ifs.empty() == true)
                break;
            else
            {
                if (record[ifs.top()].first == TWB::ADEV)
                {
                    code.append("}\nelse\n{\n");
                    st = ifs.top()->nodes[1];
                    record[ifs.top()].first = TWB::FALS;
                }
                else if (record[ifs.top()].first == TWB::FALS)
                {
                    code.append("return 0;\n}\n");
                    ifs.pop();
                }
            }
        }
    }
    code.append("}");
    std::cout << "Translation succesfull" << std::endl;
    return code;
}