#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_QUESTIONS = 100; // �����Ŀ����


class Question {
public:
    string content;
    string options[4];
    char answer;
};


class QuestionBank {
private:
    Question questions[MAX_QUESTIONS];


public:
    int numQuestions;
    QuestionBank() : numQuestions(0) {}

    void addQuestion(const Question& question) {
        if (numQuestions < MAX_QUESTIONS) {
            questions[numQuestions] = question;
            numQuestions++;
            cout << "��Ŀ��ӳɹ���" << endl;
            system("pause");
            system("cls");
        }
        else {
            cout << "��Ŀ���������޷���Ӹ�����Ŀ��" << endl;
            system("pause");
            system("cls");
        }
    }

    Question* searchQuestion(const string& content) {
        for (int i = 0; i < numQuestions; i++) {
            if (questions[i].content == content) {
                return &questions[i];
            }
        }
        return nullptr;
    }

    void modifyQuestion(const string& content, const string& newContent, char newAnswer) {
        Question* question = searchQuestion(content);
        if (question != nullptr) {
            question->content = newContent;
            question->answer = newAnswer;
            cout << "��Ŀ�޸ĳɹ���" << endl;
            system("pause");
            system("cls");
        }
        else {
            cout << "δ�ҵ�����Ŀ��" << endl;
            system("pause");
            system("cls");
        }
    }

    Question getRandomQuestion() const {
        srand(time(nullptr));
        int index = rand() % numQuestions;
        return questions[index];
    }
};

// ����ϵͳ��
class TestSystem {
private:
    QuestionBank questionBank;
    Question testQuestions[MAX_QUESTIONS];
    string username;
    int numTestQuestions;
    char userAnswers[MAX_QUESTIONS];

public:
    void addQuestion() {
        if (numTestQuestions >= MAX_QUESTIONS) {
            cout << "��Ŀ�����Ѵ����ޣ��޷���Ӹ�����Ŀ��" << endl;
            system("pause");
            system("cls");
            return;
        }

        Question question;
        cout << "��������Ŀ���ݣ�";
        getline(cin, question.content);

        for (int i = 0; i < 4; ++i) {
            cout << "������ѡ��" << static_cast<char>('A' + i) << "��";
            getline(cin, question.options[i]);
        }

        cout << "��������ȷ�𰸣�A/B/C/D����";
        cin >> question.answer;



        questionBank.addQuestion(question);
    }

    void modifyQuestion() {
        cout << "������Ҫ�޸ĵ���Ŀ���ݣ�";
        string content;
        getline(cin, content);

        Question* question = questionBank.searchQuestion(content);
        if (question != nullptr) {
            cout << "�ҵ���Ŀ��" << question->content << endl;
            cout << "�������޸ĺ����Ŀ���ݣ�";
            getline(cin, question->content);

            cout << "�������޸ĺ�Ĵ𰸣�A/B/C/D����";
            cin >> question->answer;

            cout << "��Ŀ�޸ĳɹ���" << endl;
            system("pause");
            system("cls");
        }
        else {
            cout << "δ�ҵ�����Ŀ��" << endl;
            system("pause");
            system("cls");
        }
    }

    void startTest() {
        if (questionBank.numQuestions == 0) {
            cout << "��Ŀ����Ϊ�㣬�޷����в��ԣ�" << endl;
            system("pause");
            system("cls");
            return;
        }

        cout << "�������û�����";
        getline(cin, username);

        cout << "������Ҫ���Ե���Ŀ������";
        cin >> numTestQuestions;


        cout << "���Կ�ʼ��" << endl;
        for (int i = 0; i < numTestQuestions; i++) {
            Question question = questionBank.getRandomQuestion();
            testQuestions[i] = question;
            cout << "��" << i + 1 << "�⣺" << question.content << endl;
            for (int j = 0; j < 4; j++) {
                cout << static_cast<char>('A' + j) << ". " << question.options[j] << endl;
            }

            cout << "���������Ĵ𰸣�A/B/C/D����";
            cin >> userAnswers[i];

            // �����Ƿ���ȷ
            if (userAnswers[i] == question.answer) {
                cout << "�ش���ȷ��" << endl;
            }
            else {
                cout << "�ش������ȷ���ǣ�" << question.answer << endl;
            }

            char choice;
            cout << "�Ƿ�������⣿��Y/N����";
            cin >> choice;
            if (toupper(choice) == 'N') {
                break;
            }
        }
        system("pause");
        system("cls");
    }

    void viewScore() {
        int score = 0;
        int wrongQuestionIndices[MAX_QUESTIONS];
        int numWrongQuestions = 0;
        cout << "�������û�����";
        getline(cin, username);

        for (int i = 0; i < numTestQuestions; i++) {
            Question question = testQuestions[i];

            if (toupper(testQuestions[i].answer) == toupper(userAnswers[i])) {
                score += (100 / numTestQuestions);
            }
            else {
                wrongQuestionIndices[numWrongQuestions] = i;
                numWrongQuestions++;
            }
        }

        cout << "�û�����" << username << endl;
        cout << "�÷֣�" << score << endl;
        cout << "���⣺";
        if (numWrongQuestions == 0) {
            cout << "��" << endl;
        }
        else {
            for (int i = 0; i < numWrongQuestions; i++) {
                int index = wrongQuestionIndices[i];
                Question question = testQuestions[index];
                cout << "��" << index + 1 << "�⣺" << question.content << endl;
                cout << "���Ĵ𰸣�" << userAnswers[index] << endl;
                cout << "��ȷ�𰸣�" << question.answer << endl;

                if (i < numWrongQuestions - 1) {
                    cout << endl;
                }
            }
        }
        system("pause");
        system("cls");
    }

    void showMenu() {
        cout << "��ӭʹ�ÿ��ò���ϵͳ��" << endl;
        cout << "��ѡ���ܣ�" << endl;
        cout << "1. �����¼��" << endl;
        cout << "2. �����ά��" << endl;
        cout << "3. ����" << endl;
        cout << "4. ��ѯ�ɼ�" << endl;
        cout << "5. �˳�" << endl;
    }

    void run() {
        while (true) {
            showMenu();

            int choice;
            cin >> choice;

            cin.ignore(); // ���Ի��з�

            switch (choice) {
            case 1:
                addQuestion();
                break;
            case 2:
                modifyQuestion();
                break;
            case 3:
                startTest();
                break;
            case 4:
                viewScore();
                break;
            case 5:
                cout << "��лʹ�ÿ��ò���ϵͳ���ټ���" << endl;
                return;
            default:
                cout << "��Чѡ�����������룡" << endl;
                break;
            }
        }
    }
};

int main() {
    TestSystem testSystem;
    testSystem.run();

    return 0;
}
