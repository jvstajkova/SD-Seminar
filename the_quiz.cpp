#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>

using std::cin;
using std::cout;
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::ios;

struct Result {
  char name[32];
  int questions[20];

  Result() {
    for (int i = 0; i < 20; ++i) {
      questions[i] = 0;
    }
  }

  int total() {
    int sum = 0;

    for (int i = 0; i < 20; ++i) {
      sum += questions[i];
    }

    return sum;
  }

  Result& operator+=(const Result& other) {
    for (int i = 0; i < 20; ++i) {
      questions[i] += other.questions[i];
    }

    return *this;
  }

  Result& operator-=(const Result& other) {
    for (int i = 0; i < 20; ++i) {
      questions[i] -= other.questions[i];
    }

    return *this;
  }

  Result& operator/=(const double n) {
    for (int i = 0; i < 20; ++i) {
      questions[i] /= n;
    }

    return *this;
  }

  Result& square() {
    for (int i = 0; i < 20; ++i) {
      questions[i] *= questions[i];
    }

    return *this;
  }

  Result& squareRoot() {
    for (int i = 0; i < 20; ++i) {
      questions[i] = sqrt(questions[i]);
    }

    return *this;
  }
};

istream& operator>>(istream& in, Result& result) {
  in >> result.name;
  for (int i = 0; i < 20; i++) {
    in >> result.questions[i];
  }
}

ostream& operator<<(ostream& out, const Result& result) {
  out << result.name << "\n";
  for (int i = 0; i < 20; i++) {
    out << result.questions[i] << " ";
  }
  out << "\n";
}

class QuizSaver {
  ofstream file;
public:
  QuizSaver(const char* filename) {
    file.open(filename, ios::app);
  }

  ~QuizSaver() {
    file.close();
  }

  void addResult() {
    Result result;
    cin >> result;
    file << result;

    // force writing to the file
    // for proper calculations when reading immediately
    file.flush();
  }
};

class QuizReader {
  ifstream file;

  void goToBeginningOfFile() {
    // go to beginning of file
    file.clear();
    file.seekg(0, ios::beg);
  }

  Result averageByQuestion() {
    Result total, tempResult;
    int count = 0;

    goToBeginningOfFile();

    while (file >> tempResult) {
      ++count;

      total += tempResult;
    }

    if (count > 0) {
      return total /= count;
    }
    else {
      // return zeroes if not enough results
      return total;
    }
  }

public:
  QuizReader(const char* filename) {
    file.open(filename);
  }

  ~QuizReader() {
    file.close();
  }

  Result bestResult() {
    Result bestResult, tempResult;

    goToBeginningOfFile();

    file >> bestResult;

    while (file >> tempResult) {
      if (tempResult.total() > bestResult.total()) {
        bestResult = tempResult;
      }
    }

    return bestResult;
  }

  Result bestCombinedResult() {
    Result bestResult, tempResult;

    goToBeginningOfFile();

    file >> bestResult;
    strcpy(bestResult.name, "Best combined");

    while (file >> tempResult) {
      for (int i = 0; i < 20; ++i) {
        if (tempResult.questions[i] > bestResult.questions[i]) {
          bestResult.questions[i] = tempResult.questions[i];
        }
      }
    }

    return bestResult;
  }

  Result standardDeviation() {
    Result average = averageByQuestion();
    Result sum, tempResult;
    int count = -1;

    goToBeginningOfFile();

    while (file >> tempResult) {
      ++count;
      sum += (tempResult -= average).square();
    }

    strcpy(sum.name, "Standard deviation");

    if (count > 1) {
      return (sum /= count).squareRoot();
    }
    else {
      // return zeroes if not enough results
      return sum;
    }
  }
};

int main() {
  QuizSaver quizSaver("results.txt");
  QuizReader quizReader("results.txt");

  char choice;
  cout << "Enter choice: ";
  while (cin >> choice) {
    switch (choice) {
      case 'i':
        cout << "Enter a name and 20 results:\n";
        quizSaver.addResult();
        break;
      case 'b':
        cout << "The best result is:\n";
        cout << quizReader.bestResult();
        break;
      case 'm':
        cout << quizReader.bestCombinedResult();
        break;
      case 's':
        cout << quizReader.standardDeviation();
        break;
      case 'e':
        // exit
        return 0;
      default:
        cout << "Not a valid choice. Try again!\n";
    }
    cout << "Enter choice: ";
  }

  return 0;
}
