class Database{
public:
  int width;
  int length;
  vector<Column> cols;
}

class Column{
public:
  Database parent;
  int length;
}

class Str_Column: public Column{
public:
    vector<string> vals;
}

class Num_Column: public Column{
public:
  vector<int> vals;
}
