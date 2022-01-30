#include "Trigger.h"

double Trigger::getValue()
{
	return this->value;
}

void Trigger::setValue(int newValue)
{
	this->value = newValue;
}

void Trigger::calcValue(int Value)
{
	if (Value < valueMin && Value != DEBUG_MIN)
		valueMin = value;
	if (Value > valueMax && Value != DEBUG_MIN)
		valueMax = Value;

	Value -= valueMin;

	Value /= valueMax;
}
