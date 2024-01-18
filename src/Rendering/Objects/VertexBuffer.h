#pragma once

class VertexBuffer
{
public:
    VertexBuffer();
    ~VertexBuffer();

    void set_data(void *data, unsigned int size);
    void bind() const;
    void unbind() const;
    void free();

private:
    unsigned int m_id;
    bool m_freed;
};