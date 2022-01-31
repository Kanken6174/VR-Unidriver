#pragma once
class VRTrigger : VRComponent {
private:
	double value;
public:
	VRTrigger(double val);
	~VRTrigger();

	void setValue(double val);
	double getValue();

};