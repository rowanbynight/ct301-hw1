#include "element.h"
#include "operation.h"


virtual double Operation::Value() const {
    if (this->isDouble) {
        return this->left->DoubleValue();
    }
    else {
        return this->IntValue();
    }
}