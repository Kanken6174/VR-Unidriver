struct ReceiverStr {
public:
	ReceiverStr() {};
	virtual ~ReceiverStr() {};
	virtual float receive(std::list<Prop> d) const = 0;
};


class Receiver : ReceiverStr {
public:

	Receiver() {};
	~Receiver() {};
	virtual float receive(std::list<Prop> d) const = 0;
};
