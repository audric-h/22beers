#ifndef CASE_H
#define CASE_H

namespace quoridor {

class Case {
private:

    int idPlayerOnMe_;
    bool marqued_;

public:

    Case();
    bool isThereAPlayerOnMe();
    int getIdPlayerOnMe() const;
    void setIdPlayerOnMe(int id);
    bool isMarqued() const;
    void setMarqued();
    void setNoMarqued();

};

}

#endif // CASE_H
