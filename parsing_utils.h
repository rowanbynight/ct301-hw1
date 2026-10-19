#ifndef PARSING_UTILS_H
#define PARSING_UTILS_H

const std::string MLT_OPERATOR = "*";
const std::string DIV_OPERATOR = "/";
const std::string ADD_OPERATOR = "+";
const std::string SUB_OPERATOR = "-";
const std::string MOD_OPERATOR = "%";

bool token_is_operator(std::string token);
bool token_is_numeric(std::string token);
void validate_operand_token(std::string token);
void validate_operator_token(std::string token);
void ParseOperationToken(std::string operationToken, std::string &left, std::string &right, std::string &op);

#endif