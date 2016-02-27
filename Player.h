#ifndef PLAYER_H
#define PLAYER_H

class Board;

class Player
{
public:
    Player();
    Player(const int& numero);

    void move(Board& board, const int &di, const int &dj);
    bool canMove(const Board& board, const int& di, const int& dj) const;

    const int& getNumero() const {
        return m_numero;
    }

    const int& getIPos() const {
        return m_iPos;
    }
    void setIPos(const int& i) {
        m_iPos = i;
    }

    const int& getJPos() const {
        return m_jPos;
    }
    void setJPos(const int& j) {
        m_jPos = j;
    }

private:
    int m_numero;

    int m_iPos;
    int m_jPos;
};

#endif // PLAYER_H
