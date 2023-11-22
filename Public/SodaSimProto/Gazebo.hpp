
#include <vector>
#include <stdexcept>

namespace soda {

struct Vector3D {
    Vector3D(){}
    Vector3D(float _x, float _y, float _z): x(_x), y(_y), z(_z){}
    float x = 0, y = 0, z = 0;
};

struct DataSerializer{

    DataSerializer(unsigned int magic):
        magic_(magic){}

    template<typename T>
    inline void Push(const T & val){
        sbuf->resize(sbuf->size() + sizeof(T));
        *(T*)&(*sbuf)[sbuf->size() - sizeof(T)] = val;
    }

    template <typename T>
    inline void Pull(T & val) {
        if(dind + sizeof(T) > dbuf_size)
            throw std::runtime_error("DataSerializer::BufferPush(): buffer overflow");
        val = *(T*)&dbuf[dind];
        dind += sizeof(T);
    }

    inline void PushVector(const Vector3D & val){
        size_t bsize = sbuf->size();
        sbuf->resize(sbuf->size() + sizeof(float) * 3);
        *(float*)&(*sbuf)[bsize] = val.x;
        *(float*)&(*sbuf)[bsize + sizeof(float) ] = val.y;
        *(float*)&(*sbuf)[bsize + sizeof(float) * 2 ] = val.z;
    }

    inline void PullVector(Vector3D & val) {
        if(dind + sizeof(float) * 3 > dbuf_size)
            throw std::runtime_error("DataSerializer::BufferPullVector(): buffer overflow");
        val.x = *(float*)&dbuf[dind];
        val.y = *(float*)&dbuf[dind + sizeof(float) ];
        val.z = *(float*)&dbuf[dind + sizeof(float) * 2];
        dind += sizeof(float) * 3;
    }



    virtual void Serialize(std::vector<unsigned char> & buf) = 0;
    virtual void Deserialize(const unsigned char * buf, std::size_t buf_size) = 0;

protected:
    inline void  BeginSerialize(std::vector<unsigned char> & buf) {
        buf.clear();
        sbuf = &buf;
        Push(magic_);
    }

    inline void BeginDeserialize(const unsigned char * buf, std::size_t buf_size) {
        dbuf = buf;
        dbuf_size = buf_size;
        dind = 0;
        unsigned int read_magic;
        Pull(read_magic);
        if(read_magic != magic_)
            throw std::runtime_error("ModelState::BeginDeserialize wrong magic number");
    }

private:
    unsigned int magic_;
    std::vector<unsigned char> * sbuf = 0;
    const unsigned char * dbuf = 0;
    std::size_t dbuf_size = 0;
    int dind = -1;
};


struct ModelState: public DataSerializer {

    ModelState() : DataSerializer(0xAA55AA55){}

    int msg_id = -1;
    int last_collision_msg = -1;
    std::int64_t timestamp = 0;
    Vector3D position;
    float yaw = 0;
    float pitch = 0;
    float roll = 0;
    Vector3D liner_velocity;
    Vector3D angular_velocity;
    Vector3D liner_acceleration;
    Vector3D angular_acceleration;
    float add_acc_z = 0;
    std::vector<float> chanels;

    void Serialize(std::vector<unsigned char> & buf) {
        BeginSerialize(buf);
        Push(msg_id);
        Push(last_collision_msg);
        Push(timestamp);
        PushVector(position);
        Push(yaw);
        Push(pitch);
        Push(roll);
        PushVector(liner_velocity);
        PushVector(angular_velocity);
        PushVector(liner_acceleration);
        PushVector(angular_acceleration);
        Push(add_acc_z);
        size_t chs = chanels.size();
        Push(chs);
        for(std::size_t i = 0; i < chs; i++)
            Push(chanels[i]);
    }

    void Deserialize(const unsigned char * buf, std::size_t buf_size) {
        BeginDeserialize(buf, buf_size);
        Pull(msg_id);
        Pull(last_collision_msg);
        Pull(timestamp);
        PullVector(position);
        Pull(yaw);
        Pull(pitch);
        Pull(roll);
        PullVector(liner_velocity);
        PullVector(angular_velocity);
        PullVector(liner_acceleration);
        PullVector(angular_acceleration);
        Pull(add_acc_z);
        size_t chs;
        Pull(chs);
        chanels.resize(chs);
        for(std::size_t i = 0; i < chanels.size(); i++)
            Pull(chanels[i]);
    }
};

struct ModelCollision : public DataSerializer {

    ModelCollision() : DataSerializer(0xAA55AA56){}

    int msg_id = -1;
    int last_state_msg = -1;
    std::int64_t timestamp;
    Vector3D position;
    float yaw = 0;
    float pitch = 0;
    float roll = 0;
    Vector3D liner_velocity;
    Vector3D angular_velocity;
    Vector3D hit_location;
    Vector3D hit_normal;
    Vector3D hit_normal_impulse;

    void Serialize(std::vector<unsigned char> & buf) {
        BeginSerialize(buf);
        Push(msg_id);
        Push(last_state_msg);
        Push(timestamp);
        PushVector(position);
        Push(yaw);
        Push(pitch);
        Push(roll);
        PushVector(liner_velocity);
        PushVector(angular_velocity);
        PushVector(hit_location);
        PushVector(hit_normal);
        PushVector(hit_normal_impulse);
    }

    void Deserialize(const unsigned char * buf, std::size_t buf_size) {
        BeginDeserialize(buf, buf_size);
        Pull(msg_id);
        Pull(last_state_msg);
        Pull(timestamp);
        PullVector(position);
        Pull(yaw);
        Pull(pitch);
        Pull(roll);
        PullVector(liner_velocity);
        PullVector(angular_velocity);
        PullVector(hit_location);
        PullVector(hit_normal);
        PullVector(hit_normal_impulse);
    }

};

}

