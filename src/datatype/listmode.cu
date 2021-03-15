//
// Created by Minghao Guo on 2021/3/1.
//

#include "listmode.h"
#include "../../src/include/arithmetic.h"

Listmode Listmode::operator+ (const float v) { return this->UpdateData(this->data + v); }
Listmode Listmode::operator- (const float v) { return this->UpdateData(this->data - v); }
Listmode Listmode::operator* (const float v) { return this->UpdateData(this->data * v); }
Listmode Listmode::operator/ (const float v) { return this->UpdateData(this->data * v); }

Listmode Listmode::operator+ (Listmode & v) {return this->UpdateData(this->data + v.GetData());}
Listmode Listmode::operator- (Listmode & v) {return this->UpdateData(this->data - v.GetData());}
Listmode Listmode::operator* (Listmode & v) {return this->UpdateData(this->data * v.GetData());}
Listmode Listmode::operator/ (Listmode & v) {return this->UpdateData(this->data / v.GetData());}
//Listmode Listmode::true_div (Listmode & v) {return this->UpdateData(true_div<float>(this->data, v.GetData()));}


Listmode operator+ (const float v, Listmode & other) { return other.UpdateData(v + other.GetData()); }
Listmode operator- (const float v, Listmode & other) { return other.UpdateData(v - other.GetData()); }
Listmode operator* (const float v, Listmode & other) { return other.UpdateData(v * other.GetData()); }
Listmode operator/ (const float v, Listmode & other) { return other.UpdateData(v / other.GetData()); }
