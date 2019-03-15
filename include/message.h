#include <Arduino.h>

class Message {    
    public:
        Message();
        ~Message();
        bool addData(uint8_t index, byte msb, byte lsb);
        bool addData(uint8_t index, int16_t);
        bool hasKey(uint8_t);
        uint16_t getData(uint8_t);
        uint8_t getData(uint8_t, uint8_t);
        uint8_t dataLength();
        bool isEmpty();
        void serialize(uint8_t (&inp)[20]);
    private:
        uint8_t buffer[20];
        uint8_t cursor;
};

Message::Message(){
    cursor = 0;
}

Message::~Message(){    
}

bool Message::addData(uint8_t index, byte msb, byte lsb){
    if(cursor < 17){
        buffer[cursor] = index; 
        cursor++;
        buffer[cursor] = msb; 
        cursor++;
        buffer[cursor] = lsb; 
        cursor++;
        return true;
    }
    return false;
}

bool Message::addData(uint8_t index, int16_t data){
    byte data_msb = byte(data >> 8);
    byte data_lsb = byte(data);
    return addData(index, data_msb, data_lsb);
}

bool Message::hasKey(uint8_t key){
    for(int i = 0; i < cursor; i+=3){
        if(key == buffer[i]){
            return true;
        }
    }
    return false;
}

uint16_t Message::getData(uint8_t key){
    for(int i = 0; i < cursor; i+=3){
        if(key == buffer[i]){
            return (buffer[i+1] << 8) | (buffer[i+2]);
        }
    }
}

uint8_t Message::getData(uint8_t key, uint8_t index){
    for(int i = 0; i < cursor; i+=3){
        if(key == buffer[i]){
            return buffer[i + 1 + index];
        }
    }
}

bool Message::isEmpty(){
    bool empty = (cursor == 0);
    return !empty;
}

uint8_t Message::dataLength(){
    return cursor;
}

void Message::serialize(uint8_t (&inp)[20]){
    for(int i = 0; i < cursor; i++){
        inp[i] = buffer[i];
    }
}