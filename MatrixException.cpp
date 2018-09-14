//
// Created by matteo on 14/09/18.
//

#include "MatrixException.h"

MatrixException::MatrixException(std::string whatMsg) : std::runtime_error(whatMsg) {

}
