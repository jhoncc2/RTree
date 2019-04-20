

class A {
    public:
        int var= 9993;
        int a;
        virtual int show(A* ac){
            a = 1;
            return 3;
        }

        virtual int ame(){
            return var;
        }

        static A* create(){
            return new A;
        }
};
class B : public A {

    public:
        int var = 888;
        int show (A* ac){
            a = 2;
            return ac->a;
        }

        int show2 (A* ac){
            a = 2;
            return A::ame();
        }

        static B* create(){
            return new B;
        }
};


void print(vector<ifstream*> fs){
    std::string s;
    std::getline(*fs[0], s);
    std::cout<< s << endl;
}

// test clases
int mai2n() {
    B* b = B::create();
    A* a = b;
    B* c = dynamic_cast<B*>(a);
    std::cout << c->show(a) << endl;
    std::cout << c->show2(a) << endl;

    std::istringstream iss("1,asdf,ds");
    std::string segment;
    std::getline(iss, segment, ',');
    int num = std::stoi(segment, nullptr);
    std:: cout << num << endl;

    std::vector <A*> as;

    as.push_back(new A());
    as.push_back(new A());
    A** add = as.data();
    std::cout << add[0]->show(new A()) << endl;
    std::cout << add[1]->show(new A()) << endl;
    A* aaa = as.back();
    std::cout << as.size() << endl;
    A* addfa[2];
    addfa[0] = as.back();
    addfa[1] = as.back();
    std::cout << addfa[1] << endl;

    std::vector<ifstream*> fs;
    std::ifstream f;
    std::string s = "tmp/output.sorted";
    f.open(s.c_str(), ios::in);
    fs.push_back(&f);
    std::getline(*fs[0], s);
    std::cout<< s << endl;
    print(fs);
}
