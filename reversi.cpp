#include<vector>
#include <iostream>
#include <bitset>
#include <map>
#include <chrono> 
#include <string.h>
#include <chrono>
#include <thread>
using namespace std::chrono_literals;
using namespace std;
using namespace chrono;
struct State {
    bitset<64> black;
    bitset<64> white;
    State() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                black[i * 8 + j] = 0;
                white[i * 8 + j] = 0;
                if(i==j && (i == 4 || i==3))
                    white[i * 8 + j] = 1;
                else if( (i==4 && j==3)||((i == 3 && j == 4)))
                    black[i * 8 + j] = 1;

            }
        }
    }
    void Print() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                int ind = i * 8 + j;
                if (black[ind] == white[ind])
                    cout << "- ";
                else if (white[ind])
                    cout << "W ";
                else if (black[ind])
                    cout << "B ";

            }
            cout << endl;
        }
        cout << endl;
    }
    int evaluate() const {
        int sum = 0;
        for (int i = 0; i < 64; i++) {
            if (black[i])
                sum++;
            if (white[i])
                sum--;
        }
        return sum;
    }
    int count_black() const {
        int sum = 0;
        for (int i = 0; i < 64; i++) {
            if (black[i])
                sum++;
        }
        return sum;
    }
    int count_white() const {
        int sum = 0;
        for (int i = 0; i < 64; i++) {
            if (white[i])
                sum++;
        }
        return sum;
    }
    int count_emp() const {
        int sum = 0;
        for (int i = 0; i < 64; i++) {
            if (white[i]==black[i])
                sum++;
        }
        return sum;
    }

};

bool NotFindState(vector<State> vect, State st) {
    for (State x : vect) {
        if (x.black != st.black || x.white != st.white)
            return false;
    }
    return true;
}

map< int, State> LastNewStates(map<int, vector<State>> mp, bool player) {
    vector<int> vr = { 1,-1,0 };
    map< int, State> res;
    int x, y, index;
    if (player) {
        for (auto m : mp) {
            State a = m.second[0];
            if (m.second.size() > 1) {
                a = m.second[0];
                for (int i = 1; i < m.second.size(); i++) {
                    State b = m.second[i];

                    for (int a1 : vr) {
                        for (int a2 : vr) {
                            if (!(a1 == 0 && a2 == 0)) {
                                int delta = a2 * 8 + a1;
                                index = m.first;
                                x = index % 8;
                                y = index / 8;
                                while (x + a1 <= 7 && x + a1 >= 0 && y + a2 <= 7 && y + a2 >= 0 && b.black[index + delta] && !a.black[index + delta]) {
                                    a.black[index + delta] = player;
                                    a.white[index + delta] = !player;
                                    index += delta;
                                    x = index % 8;
                                    y = index / 8;
                                }
                            }
                        }
                    }
                }

            }
            res[m.first]=a;
            
        }
    }
    else {
        for (auto m : mp) {
            State a = m.second[0];
            if (m.second.size() > 1) {
                a = m.second[0];
                for (int i = 1; i < m.second.size(); i++) {
                    State b = m.second[i];

                    for (int a1 : vr) {
                        for (int a2 : vr) {
                            if (!(a1 == 0 && a2 == 0)) {
                                int delta = a2 * 8 + a1;
                                index = m.first;
                                x = index % 8;
                                y = index / 8;
                                while (x + a1 <= 7 && x + a1 >= 0 && y + a2 <= 7 && y + a2 >= 0 && b.white[index + delta] && !a.white[index + delta]) {
                                    a.black[index + delta] = player;
                                    a.white[index + delta] = !player;
                                    index += delta;
                                    x = index % 8;
                                    y = index / 8;
                                }
                            }
                        }
                    }
                }
            }
            res[m.first]=a;
        }

    }
    return res;
    

}
bool IsNewState(State st, bool player) {
    int x, y;
    vector<int> vr = { 1,-1,0 };
    if (player) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                int ind = i * 8 + j;
                if (st.black[ind] == 1) {


                    for (int a1 : vr) {
                        for (int a2 : vr) {
                            if (!(a1 == 0 && a2 == 0)) {
                                int delta = a2 * 8 + a1;
                                //State new_state = st;
                                int start = i * 8 + j;
                                ind = i * 8 + j;
                                x = ind % 8;
                                y = ind / 8;
                                while (x + a1 <= 7 && x + a1 >= 0 && y + a2 <= 7 && y + a2 >= 0 && st.white[ind + delta]) {
                                    ind += delta;
                                    x = ind % 8;
                                    y = ind / 8;
                                }
                                if (x + a1 <= 7 && x + a1 >= 0 && y + a2 <= 7 && y + a2 >= 0 && ind != start && !st.black[ind + delta]) {
                                    

                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                int ind = i * 8 + j;
                if (st.white[ind] == 1) {


                    for (int a1 : vr) {
                        for (int a2 : vr) {
                            if (!(a1 == 0 && a2 == 0)) {
                                int delta = a2 * 8 + a1;
                                
                                int start = i * 8 + j;
                                ind = i * 8 + j;
                                x = ind % 8;
                                y = ind / 8;
                                while (x + a1 <= 7 && x + a1 >= 0 && y + a2 <= 7 && y + a2 >= 0 && st.black[ind + delta]) {
                                    ind += delta;
                                    x = ind % 8;
                                    y = ind / 8;
                                }
                                if (x + a1 <= 7 && x + a1 >= 0 && y + a2 <= 7 && y + a2 >= 0 && ind != start && !st.white[ind + delta]) {
                                   

                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }

    }
    
    return false;


}
map <int, State> MakeNewStates(State& st, bool player) {
    map<int,vector<State>> indLastBlack;
    int x, y;
    vector<int> vr = { 1,-1,0};
    
    if (player) {
        bool many_cell = st.count_black() > st.count_emp();
        if (many_cell) {
            map<int, State> rs;
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    int ind = i * 8 + j;
                    if (st.black[ind] == st.white[ind])
                    {
                        State new_state = st;
                        for (int a1 : vr) {
                            for (int a2 : vr) {
                                if (!(a1 == 0 && a2 == 0)) 
                                {
                                    int delta = a2 * 8 + a1;
                                    int start = i * 8 + j;
                                    ind = i * 8 + j;
                                    x = ind % 8;
                                    y = ind / 8;
                                    while (x + a1 <= 7 && x + a1 >= 0 && y + a2 <= 7 && y + a2 >= 0 && new_state.white[ind + delta]) {
                                        ind += delta;
                                        x = ind % 8;
                                        y = ind / 8;
                                    }
                                    if (x + a1 <= 7 && x + a1 >= 0 && y + a2 <= 7 && y + a2 >= 0 && ind != start && new_state.black[ind + delta]) {
                                        for (int k = 0; k <= abs(ind - start) / abs(delta); k++) {
                                            new_state.black[start + k * delta] = player;
                                            new_state.white[start + k * delta] = !player;
                                        }

                                        rs[start] = new_state;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            return rs;

        }
        else {
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    int ind = i * 8 + j;
                    if (st.black[ind] == 1) {


                        for (int a1 : vr) {
                            for (int a2 : vr) {
                                if (!(a1 == 0 && a2 == 0)) {
                                    int delta = a2 * 8 + a1;
                                    State new_state = st;
                                    int start = i * 8 + j;
                                    ind = i * 8 + j;
                                    x = ind % 8;
                                    y = ind / 8;
                                    while (x + a1 <= 7 && x + a1 >= 0 && y + a2 <= 7 && y + a2 >= 0 && new_state.white[ind + delta]) {
                                        ind += delta;
                                        x = ind % 8;
                                        y = ind / 8;
                                    }
                                    if (x + a1 <= 7 && x + a1 >= 0 && y + a2 <= 7 && y + a2 >= 0 && ind != start && !new_state.black[ind + delta]) {
                                        for (int k = 0; k <= abs(ind - start) / abs(delta); k++) {
                                            new_state.black[start + (k + 1) * delta] = player;
                                            new_state.white[start + (k + 1) * delta] = !player;
                                        }

                                        indLastBlack[ind + delta].push_back(new_state);
                                    }
                                }
                            }
                        }
                    }


                }
            }
        }
    }
    else {
        bool many_cell = st.count_white() > st.count_emp();
        if (many_cell) {
            map<int, State> rs;
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    int ind = i * 8 + j;
                    if (st.black[ind] == st.white[ind])
                    {
                        State new_state = st;
                        for (int a1 : vr) {
                            for (int a2 : vr) {
                                if (!(a1 == 0 && a2 == 0))
                                {
                                    int delta = a2 * 8 + a1;
                                    int start = i * 8 + j;
                                    ind = i * 8 + j;
                                    x = ind % 8;
                                    y = ind / 8;
                                    while (x + a1 <= 7 && x + a1 >= 0 && y + a2 <= 7 && y + a2 >= 0 && new_state.black[ind + delta]) {
                                        ind += delta;
                                        x = ind % 8;
                                        y = ind / 8;
                                    }
                                    if (x + a1 <= 7 && x + a1 >= 0 && y + a2 <= 7 && y + a2 >= 0 && ind != start && new_state.white[ind + delta]) {
                                        for (int k = 0; k <= abs(ind - start) / abs(delta); k++) {
                                            new_state.black[start + k * delta] = player;
                                            new_state.white[start + k * delta] = !player;
                                        }

                                        rs[start] = new_state;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            return rs;

        }
        else {
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    int ind = i * 8 + j;
                    if (st.white[ind] == 1) {


                        for (int a1 : vr) {
                            for (int a2 : vr) {
                                if (!(a1 == 0 && a2 == 0)) {
                                    int delta = a2 * 8 + a1;
                                    State new_state = st;
                                    int start = i * 8 + j;
                                    ind = i * 8 + j;
                                    x = ind % 8;
                                    y = ind / 8;
                                    while (x + a1 <= 7 && x + a1 >= 0 && y + a2 <= 7 && y + a2 >= 0 && new_state.black[ind + delta]) {
                                        ind += delta;
                                        x = ind % 8;
                                        y = ind / 8;
                                    }
                                    if (x + a1 <= 7 && x + a1 >= 0 && y + a2 <= 7 && y + a2 >= 0 && ind != start && !new_state.white[ind + delta]) {
                                        for (int k = 0; k <= abs(ind - start) / abs(delta); k++) {
                                            new_state.black[start + (k + 1) * delta] = player;
                                            new_state.white[start + (k + 1) * delta] = !player;
                                        }

                                        indLastBlack[ind + delta].push_back(new_state);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

    }
    auto res=LastNewStates(indLastBlack, player);
    return res;
  
    
}
int Evristic(State& st, bool player) {
    int sum = 0;
    
    sum += st.evaluate();
    if (!player)
        sum = -sum;

    if (player) {  // Для черных
        for (int i = 0; i < 64; i++) {
            int x = i % 8;
            int y = i / 8;

            // Угловые клетки
            if ((x == 0 || x == 7) && (y == 0 || y == 7)) {
                if (st.black[i])
                    sum += 10;
                else if (st.white[i])
                    sum -= 10;
            }
            // Клетки на границах доски
            else if ((x == 0 || y == 0 || x == 7 || y == 7)) {
                
                if (st.black[i]) {
                    sum += 5;
                }
                else if (st.white[i]) {
                    sum -= 5;
                }
            }
        }
    }
    else {  // Для белых
        for (int i = 0; i < 64; i++) {
            int x = i % 8;
            int y = i / 8;

            // Угловые клетки
            if ((x == 0 || x == 7) && (y == 0 || y == 7)) {
                if (st.white[i])
                    sum += 10;
                else if (st.black[i])
                    sum -= 10;
            }
            // Клетки на границах доски
            else if ((x == 0 || y == 0 || x == 7 || y == 7)) {
                
                if (st.white[i]) {
                    sum += 5;
                }
                else if (st.black[i]) {
                    sum -= 5;
                }
            }
        }
    }

    return sum;
}

// Алгоритм Минимакс с альфа-бета отсечением
int minimax(State& board, int depth, int alpha, int beta, bool maximizingPlayer) {
    //auto pl = MakeNewStates(board, 1);
    //auto op = MakeNewStates(board, 0);
    if (depth == 0){// || (!IsNewState(board, 1)  !IsNewState(board, 0))) {
        return Evristic(board,maximizingPlayer);
    }

    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        /*if(!IsNewState(board, 1))
            return minimax(board, depth - 1, alpha, beta, false);*/
        for (auto& move : MakeNewStates(board, 1)) {
            State mov = move.second;
            int eval = minimax(mov, depth - 1, alpha, beta, false);
            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);
            if (beta <= alpha) break;
        }
        if(maxEval == std::numeric_limits<int>::min())
           return minimax(board, depth - 1, alpha, beta, true);
        return maxEval;
    }
    else {
        int minEval = std::numeric_limits<int>::max();
       /* if (!IsNewState(board, 0))
            return minimax(board, depth - 1, alpha, beta, true);*/
        for (auto& move : MakeNewStates(board, 0)) {
            State mov = move.second;
            int eval = minimax(mov, depth - 1, alpha, beta, true);
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if (beta <= alpha) break;
        }
        if(minEval== std::numeric_limits<int>::max())
            return minimax(board, depth - 1, alpha, beta, false);
        return minEval;
    }
}

// Найти лучший ход для игрока
pair<State, int> findBestMove(State& board, int player) {
    int bestValue = std::numeric_limits<int>::min();
    State bestMove;
    int cell;
    int dep = 7;
    if (board.count_emp()<=56) {
        dep = 5;
        cout << "B="<< board.count_black() <<endl;
    }
    
    auto m = MakeNewStates(board, player);
    for (auto& move : m) {
        State mov = move.second;
        int moveValue = minimax(mov,7, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), !player);
        if (moveValue > bestValue) {
            bestMove = mov;
            cell = move.first;
            bestValue = moveValue;
        }
    }
    return make_pair(bestMove, cell);
}
vector<State> IsValidOppStep(State st, int player,int check_x, int check_y) {
    vector<State> vect;
    if (!(check_x >= 0 && check_x <= 7 && check_y >= 0 && check_y <= 7))
        return vect;
    int ind = check_y * 8 + check_x;
    
    if (st.black[ind] || st.white[ind])
        return vect;
    if (player) {
        auto m = MakeNewStates(st, player);
        for (auto& move : m) {
            if (move.second.black[ind]) {
                vect.push_back(move.second);
                break;
            }
        }

    }
    else {
        auto m = MakeNewStates(st, player);
        for (auto& move : m) {
            if (move.second.white[ind]) {
                vect.push_back(move.second);
                break;
            }
        }
    }
    return vect;
    

}
int main(int argc, char* argv[])
{
 
    auto start_time = high_resolution_clock::now();
    
    int color = atoi(argv[argc - 1]);//0 ЧЕРНЫЙ 1 белый
    string step;
    int x, y;
    State board;
    board.Print();
    bool currentPlayer = 1;
    int cell;
    auto pl = IsNewState(board, currentPlayer);
    auto op = IsNewState(board, !currentPlayer);
    while (pl || op) {
        State move;
        if (IsNewState(board, currentPlayer)) {
            cout << "Player " << (currentPlayer?"BLACK":"WHITE") << endl;
            if (currentPlayer != color) {
                auto find = findBestMove(board, currentPlayer);
                move = find.first;
                cell = find.second;
                board = move;
                char letter = 'a' + cell % 8;  // Преобразование числа в букву
                char number = '1' + cell / 8;  // Преобразование индекса в число

                cerr << string(1, letter) + string(1, number) << endl;
                board.Print();
            }
            else {
                cin >> step;
                x = step[0] - 'a';
                y= step[1] - '1';
                vector<State> vr = IsValidOppStep(board, currentPlayer, x, y);
                while (vr.empty())
                {
                    cin >> step;
                    x = step[0] - 'a';
                    y = step[1] - '1';
                    vr = IsValidOppStep(board, currentPlayer, x, y);
                }
                board =vr[0];
                board.Print();
                
            }
            
            
        }
        else {
            cout << "Player " << currentPlayer << " can't move. " << endl;
        }
        currentPlayer = !currentPlayer;
        pl = IsNewState(board, currentPlayer);
        op = IsNewState(board, !currentPlayer);
    }

    std::cout << "Игра окончена!" << std::endl;
     auto end_time = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end_time - start_time);

    cout << "Time: " << duration.count() << " ml" << endl;
    if (color) {
        if (board.count_black() < board.count_white())
            exit(0);
        else if (board.count_black() > board.count_white())
            exit(3);
        else
            exit(4);
    }
    else {
        if (board.count_black() > board.count_white())
            exit(0);
        else if (board.count_black() < board.count_white())
            exit(3);
        else
            exit(4);
    }


   

}

