class Com
{
private:
    uint8_t header;
    Message queue;
public:
    Com(uint8_t head);
    ~Com();
    bool available(Stream& uart);
    void send(Stream& uart, Message input);
    Message readQueue();
};

Com::Com(uint8_t head){
    header = head;
}

Com::~Com(){}

bool Com::available(Stream& uart){
    if(uart.available()){
        uint8_t head[2];
        uart.readBytes(head, 2);
        if(head[0] == header){
            uint8_t len = head[1];
            uint8_t buffer[len+1];
            if(len%3 == 0){
                uart.readBytes(buffer, len+1);
                uint8_t checksum = 0;
                for(int i = 0; i<len; i++){
                    checksum += buffer[i];
                }
                if(byte(0xFF-checksum) == byte(buffer[len])){
                    Message new_message;
                    for(int i=0; i<len; i+=3){
                        new_message.addData(buffer[i], buffer[i+1], buffer[i+2]);
                    }
                    queue = new_message;
                    return true;
                }
            }

        }
    }
    return false;
}

Message Com::readQueue(){
    Message tmp_queue = queue;
    queue = Message();
    return tmp_queue;
}

void Com::send(Stream& uart, Message input){
    uint8_t msg_len = input.dataLength();
    uint8_t total_len = 3 + msg_len;
    uint8_t cursor = 0;
    uint8_t output[total_len];
    
    uint8_t msg_buffer[20];
    input.serialize(msg_buffer);

    output[cursor] = header; cursor++;
    output[cursor] = input.dataLength(); cursor++;

    int check_sum = 0;
    
    for(int i = 0; i < msg_len; i++){
        output[cursor] = msg_buffer[i];
        check_sum += msg_buffer[i];
        cursor++;
    }

    output[cursor] = byte(0xFF-check_sum);
    
    for(int i = 0; i < total_len; i++){
        uart.write(output[i]);
    }
}