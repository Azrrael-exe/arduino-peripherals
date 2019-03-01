
class Universal: public Peripheal {
private:
    Task<Message, Message> tasks[10];
    Message output[10];
public:
    void attach(int index, Message (*fun)(Message));
    Message run(int index, Message);
    Message readResult(int index, Message, bool force);
};

void Universal::attach(int index, Message (*fun)(Message)){
    tasks[index].attach(fun);
}

Message Universal::run(int index, Message params = Message()){
    output[index] = tasks[index].run(params);
    return output[index];
}

Message Universal::readResult(int index, Message params = Message() ,bool force=false){
    if(force || output[index].isEmpty()){
        run(index, params);
    }
    return output[index];
}
