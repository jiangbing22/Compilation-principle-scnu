#include "LALR.h"


std::string LALR::countcore(std::unordered_set<LR1Item> itemset)
{

    // �ռ���ǰ�ڵ�ĺ�����Ŀ��
    std::unordered_set <std::string> coreset;
    for (const auto& item : itemset) {
        std::string str = item.lhs;
        str += "=";
        for (auto j : item.rhs)
        {
            str += j;
            str += "&";
        }
        str += item.dotPos;
        coreset.insert(str);
    }
    std::string result;
    for (auto i : coreset)
    {
        result += i;
        result += "\n";
    }
    std::cout << result;
    return result;
}

// �հ����������ڼ���LR1��Ŀ���ıհ���
std::unordered_set<LR1Item> LALR::closure(const std::unordered_set<LR1Item>& items) {
    std::unordered_set<LR1Item> closureSet = items; // ��ʼ���հ���Ϊ�������Ŀ��
    bool added; // ����Ƿ��ڵ��������������Ŀ
    do {
        added = false; // ÿ��ѭ����ʼʱ���ٶ�û���������Ŀ
        for (const auto& item : closureSet) {
            if (item.dotPos < item.rhs.size()) { // ��δ�������ʽ�Ҳ��ĩβ
                std::string symbol = item.rhs[item.dotPos]; // ��ǰ����ķ���
                if (G.unendSet.find(symbol) != G.unendSet.end()) { // ������ս��������հ�
                    // ����ÿ����symbolΪ�����ŵĲ���ʽ�������µ�LR1��Ŀ
                    for (const auto& prod : G.ex_G) {
                        if (prod.left == symbol) {
                            std::unordered_set<std::string> lookaheads; // ��ʼ��lookahead����
                            // ����lookahead����
                            if (item.dotPos + 1 < item.rhs.size()) {
                                // �������滹�з��ţ�����FIRST����
                                std::string nextSymbol;
                                bool isnull = true;
                                for (int next = item.dotPos + 1; next < item.rhs.size(); next++) {
                                    nextSymbol = item.rhs[next];
                                    if (G.unendSet.find(nextSymbol) == G.unendSet.end()) {
                                        // ������ս��������lookahead����
                                        lookaheads.insert(nextSymbol);
                                        isnull = false;
                                        break;
                                    }
                                    else if (G.nullMap[nextSymbol]) {
                                        // ����Ƿ��ս���ҿ�Ϊ�գ�����FIRST����
                                        lookaheads.insert(G.firstMap[nextSymbol].begin(), G.firstMap[nextSymbol].end());
                                        lookaheads.erase("@"); // �Ƴ��������
                                    }
                                    else {
                                        // ����Ƿ��ս���Ҳ���Ϊ�գ�����FIRST����
                                        lookaheads.insert(G.firstMap[nextSymbol].begin(), G.firstMap[nextSymbol].end());
                                        isnull = false;
                                        break;
                                    }
                                }
                                if (isnull) { // ���������з��Ŷ���Ϊ�գ�����FOLLOW����
                                    lookaheads.insert(G.followMap[symbol].begin(), G.followMap[symbol].end());
                                }
                            }
                            else {
                                // ��������û�з��ţ�ʹ�õ�ǰlookahead
                                lookaheads.insert(item.lookahead);
                            }
                            // �������ɵ�LR1��Ŀ����հ���
                            for (const auto& lookahead : lookaheads) {
                                LR1Item newItem{ symbol, prod.right, 0, lookahead };
                                if (closureSet.insert(newItem).second) {
                                    added = true; // �������Ŀ����ӣ����Ϊtrue
                                }
                            }
                        }
                    }
                }
            }
        }
    } while (added); // ������������Ŀ�����������
    return closureSet; // ���رհ���
}

// ת�ƺ��������ڼ����ڸ��������´�ĳ����Ŀ��ת�Ƶõ��µ���Ŀ����
std::unordered_set<LR1Item> LALR::gotoState(const std::unordered_set<LR1Item>& items, const std::string& symbol) {
    std::unordered_set<LR1Item> gotoSet;
    for (const auto& item : items) {
        if (item.dotPos < item.rhs.size() && item.rhs[item.dotPos] == symbol) {
            // �����µ�LR1��Ŀ���������ƶ�һλ
            gotoSet.insert({ item.lhs, item.rhs, item.dotPos + 1, item.lookahead });
        }
    }
    // �Եõ���goto�����бհ�����
    return closure(gotoSet);
}

// ����LR1�Զ���
void LALR::createLR1Automaton() {
    // ��ʼ��Ŀ����������ʼ���ŵ���ʼ��Ŀ
    std::unordered_set<LR1Item> startItems;

    startItems.insert({ G.ex_G[0].left, {G.ex_G[0].right[0]}, 0, "$" });
    head = new LR1NODE{}; // ������ʼ�ڵ�
    std::queue<std::unordered_set<LR1Item>> stateQueue; // ���ڴ洢�������״̬����
    stateQueue.push(closure(startItems)); // ����ʼ�հ������

    std::unordered_map<std::unordered_set<LR1Item>, LR1NODE*> stateMap; // ӳ�����Ŀ�����ڵ�
    stateMap[stateQueue.front()] = head; // ����ʼ�հ���ӳ�䵽��ʼ�ڵ�
    int stateNum = 0; // ״̬���

    while (!stateQueue.empty()) {
        std::unordered_set<LR1Item> currentState = stateQueue.front(); // ��ȡ��ǰ״̬
        stateQueue.pop(); // ����

        LR1NODE* currentNode = stateMap[currentState]; // ��ȡ��ǰ�ڵ�

        currentNode->stateNum = stateNum++; // ����״̬��Ų�����
        currentNode->items = currentState; // ���ýڵ����Ŀ��

        // ����ÿ�����ŵ�ת��
        std::unordered_map<std::string, std::unordered_set<LR1Item>> symbolTransitions;
        for (const auto& item : currentState) {
            if (item.dotPos < item.rhs.size()) {
                symbolTransitions[item.rhs[item.dotPos]].insert(item); // �Է���Ϊ�����洢��Ŀ
            }
        }
        // Ϊÿ�����ŵ�ת�ƴ����µĽڵ�����ӳ���
        for (const auto& transition : symbolTransitions) {
            auto symbol = transition.first;
            auto newState = gotoState(currentState, symbol); // ����ת�ƺ��״̬
            
            if (stateMap.find(newState) == stateMap.end()) {
                // �����״̬����ӳ����У������½ڵ㲢����ӳ���
                LR1NODE* newNode = new LR1NODE{};
                stateMap[newState] = newNode;
                stateQueue.push(newState); // ����״̬���
            }
            // ���µ�ǰ�ڵ��ת�Ʊ�
            currentNode->state[symbol] = stateMap[newState];
        }
    }
}

// �ϲ�ͬ����Ŀ������LALR(1)�Զ���
void LALR::createLALRAutomaton() {

    std::unordered_set<LR1Item> startItems;
    startItems.insert({ G.ex_G[0].left, {G.ex_G[0].right[0]}, 0, "$" });
    LALRhead = new LR1NODE{}; // ������ʼ�ڵ�
    std::queue<std::unordered_set<LR1Item>> stateQueue; // ���ڴ洢�������״̬����
    stateQueue.push(closure(startItems)); // ����ʼ�հ������

    std::unordered_map<std::unordered_set<LR1Item>, LR1NODE*> stateMap; // ӳ�����Ŀ�����ڵ�
    std::unordered_map<std::string, LR1NODE*> coreMap;

    coreMap[countcore(stateQueue.front())] = LALRhead;
    stateMap[stateQueue.front()] = LALRhead; // ����ʼ�հ���ӳ�䵽��ʼ�ڵ�
    int stateNum = 0; // ״̬���

    while (!stateQueue.empty()) {
        std::unordered_set<LR1Item> currentState = stateQueue.front(); // ��ȡ��ǰ״̬
        stateQueue.pop(); // ����
        LR1NODE* currentNode = stateMap[currentState]; // ��ȡ��ǰ�ڵ�
        currentNode->stateNum = stateNum++; // ����״̬��Ų�����
        currentNode->items = currentState; // ���ýڵ����Ŀ��
        indexmap.push_back(currentNode);
        // �ռ���ǰ״̬�ĺ�����Ŀ��
        currentNode->core = countcore(currentState);
        // ����ÿ�����ŵ�ת��
        std::unordered_map<std::string, std::unordered_set<LR1Item>> symbolTransitions;
        for (const auto& item : currentState) {
            if (item.dotPos < item.rhs.size()) {
                symbolTransitions[item.rhs[item.dotPos]].insert(item); // �Է���Ϊ�����洢��Ŀ
            }
        }

        // Ϊÿ�����ŵ�ת�ƴ����µĽڵ�����ӳ���
        for (const auto& transition : symbolTransitions) {
            auto symbol = transition.first;
            auto newState = gotoState(currentState, symbol); // ����ת�ƺ��״̬
            auto newcore = countcore(newState);
            if (coreMap.find(newcore) == coreMap.end()) {
                // �����״̬����ӳ����У������½ڵ㲢����ӳ���
                LR1NODE* newNode = new LR1NODE{};
                stateMap[newState] = newNode;
                coreMap[newcore] = newNode;

                stateQueue.push(newState); // ����״̬���
                // ���µ�ǰ�ڵ��ת�Ʊ�
                currentNode->state[symbol] = stateMap[newState];
            }
            else
            {
                //�ϲ�չ������
                for (auto i : newState)
                {
                    coreMap[newcore]->items.insert(i);
                }
                //newState = currentNode->items;
                //stateMap[newState] = currentNode;
            }

        }
    }
}

// ����ACTION��GOTO��
void LALR::generateParsingTable() {
    // ��ʼ��ACTION��GOTO��
    for (int i = 0; i < indexmap.size(); i++) {
        for (const auto& symbol : G.endSet) {
            actionTable[i][symbol] = "";
            actionTable[i]["$"] = "";
        }
        
        for (const auto& symbol : G.unendSet) {
            gotoTable[i][symbol] = -1;
        }
    }
    // ���ACTION��GOTO��
    for (int i = 0; i < indexmap.size();i++) {
        for (const auto& item :indexmap[i]->items) {
            if (item.dotPos == item.rhs.size()) {
                if (item.lhs == G.first) {
                    actionTable[i][item.lookahead] = "accept";
                }
                else {
                    int prodIndex = G.itemMap[item.lhs + item.rhs2str()];
                    // ��Լ
                    actionTable[i][item.lookahead] = "r" + std::to_string(prodIndex);
                }
            }
            else {
                std::string symbol = item.rhs[item.dotPos];
                if (G.unendSet.find(symbol)==G.unendSet.end()) {
                    auto nextState = indexmap[i]->state.find(symbol);
                    if (nextState != indexmap[i]->state.end()) {
                        // �ƽ�
                        actionTable[i][symbol] = "s" + std::to_string(nextState->second->stateNum);
                    }
                }
            }
        }
        // ���GOTO��
        for (const auto& j: indexmap[i]->state) {
            const auto & symbol = j.first;
            const auto& nextNode= j.second;
            if (G.unendSet.find(symbol)!= G.unendSet.end()) {
                gotoTable[i][symbol] = nextNode->stateNum;
            }
        }
    }
}
// LALR���캯��������һ���ļ�·����Ϊ����
LALR::LALR(const std::string filepath) : G(filepath), head(nullptr) {
    // ����LR1�Զ���
    createLR1Automaton();
    // ��ӡLR1�Զ�����״̬
    std::cout << "LR1 AUTOMATION\n";
    // ����LALR(1)�Զ���
    std::cout << "LALR1 AUTOMATION\n";
    createLALRAutomaton();
    // ��ӡLALR(1)�Զ�����״̬
    generateParsingTable();
    // ��ӡ�Զ���������ɵ���Ϣ
    std::cout << "create finish" << std::endl;
}

//��Լʱ�����﷨��������Ҫ:tokentype tokenstring��
//ÿ�����ʶ�Ҫ��string+type����ʽ����
//���ƽ����Լʱ������������ݡ�����Ҫ tokentype tokenstring
//��Ҫ��д����������Դ���봦��������ṹ
string LALR::Analysis(std::string filepath)
{
    std::stringstream resultss; // ʹ�� stringstream ��¼�����־
    std::ifstream infile(filepath);
    std::vector<std::pair<std::string, std::string>> tokens;

    // �ʷ�����
    if (infile.is_open()) {
        std::string sentence;
        while (std::getline(infile, sentence)) {
            std::stringstream ss(sentence);
            std::string left, assign, right;
            ss >> left >> assign >> right;
            tokens.push_back(make_pair(left, right));
        }
    }
    else {
        std::cout << "�ʷ���������";
        return "";
    }
    // ��ʼ����������
    tokens.push_back(make_pair("$", "END_C")); // ��ӽ�����
    std::stack<AI> anaStk; // ״̬ջ
    AI firstItem;
    firstItem.state = 0; // ��ʼ״̬
    anaStk.push(firstItem);

    // �﷨�����ڵ�
    std::stack<std::shared_ptr<SyntaxTreeNode>> treeStack; // ���ڴ洢���ڵ��ջ

    // ��������
    int i = 0; // �ʷ���Ԫ����
    while (!anaStk.empty()) {
        AI top = anaStk.top();
        std::string currentString = tokens[i].first;
        std::string currentToken = tokens[i].second;
        std::string act = actionTable[top.state][currentToken];

        // ����Ƿ���ڲ���
        if (act == "") {
            resultss << "������״̬ " << top.state << " ��û���ҵ� " << currentToken << " �Ĳ���\n";
            break;
        }

        // �ƽ�����
        if (act[0] == 's') {
            int nextState = std::stoi(act.substr(1));
            resultss << "�ƽ����� " << currentString<<"->"<< currentToken << " ����״̬ " << nextState << "\n";
            // �����﷨���ڵ�
            auto newNode = std::make_shared<SyntaxTreeNode>(currentToken);
            newNode->tokenString = currentString; // ��ǰ token �ַ���
            treeStack.push(newNode);

            // ����״̬ѹ��ջ��
            AI newItem;
            newItem.state = nextState;
            newItem.token = make_pair(currentString, currentToken);
            anaStk.push(newItem);
            i++; // �ƶ�����һ���ʷ���Ԫ
        }
        // ��Լ����
        else if (act[0] == 'r') {
            int prodIndex = std::stoi(act.substr(1)); // ��ȡ����ʽ����
            auto production = G.ex_G[prodIndex]; // G.ex_G �洢����ʽ

            resultss << "��Լ��ͨ������ʽ " << production.left << " -> ";
            for (const auto& symbol : production.right) {
                resultss << symbol << " ";
            }
            resultss << "\n";

            // �����﷨���ڵ�
            auto newNode = std::make_shared<SyntaxTreeNode>(production.left);
            newNode->tokenString = production.left; // ��ǰ����ʽ��
            for (const auto& symbol : production.right) {
                // ��ջ�е�����Ӧ�Ľڵ�
                if (!treeStack.empty()) {
                    newNode->children.push_back(treeStack.top());
                    treeStack.pop();
                }
            }

            // ���½ڵ�ѹ��ջ��
            treeStack.push(newNode);

            // ���ݲ���ʽ�ĳ��ȵ���״̬
            for (size_t j = 0; j < production.right.size(); j++) {
                anaStk.pop();
            }

            // ʹ�� GOTO ��ȷ����һ��״̬
            AI newTop = anaStk.top();
            int nextState = gotoTable[newTop.state][production.left];
            if (nextState == -1) {
                resultss << "������״̬ " << newTop.state << " ��û���ҵ����ս�� " << production.left << " �� GOTO\n";
                break;
            }

            // ����״̬ѹ��ջ��
            AI newItem;
            newItem.token = make_pair(production.left, "UNEND");
            newItem.state = nextState;
            anaStk.push(newItem);
        }
        // ���ܲ���
        else if (act == "accept") {
            resultss << "��������\n";
            syntaxTreeRoot = treeStack.top(); // ��ȡ�﷨�����ڵ�
            break;
        }
    }

    // �����﷨���Ĵ�ӡ�߼�����ѡ��
    if (syntaxTreeRoot) {
        resultss << "���ɵ��﷨����\n";
        printSyntaxTree(syntaxTreeRoot, resultss, 0); // �ݹ��ӡ�﷨��
    }

    // ���ط������
    return resultss.str();
}

// ��ӡ�﷨���ĸ�������
void LALR::printSyntaxTree(const std::shared_ptr<SyntaxTreeNode>& node, std::stringstream& ss, int depth) {
    for (int i = 0; i < depth; ++i) ss << "  "; // ����
    ss << node->tokenString << "\n";
    for (const auto& child : node->children) {
        printSyntaxTree(child, ss, depth + 1); // �ݹ��ӡ�ӽڵ�
    }
}


