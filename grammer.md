```
query          → selectStmt | insertStmt | createStmt ;
createStmt     → "CREATE" "TABLE" table "(" column  type ("," column type)* ")" ";" ;
selectStmt     → "SELECT" ( "*" | column ("," column)* ) "FROM" table ";" ;
insertStmt     → "INSERT" "INTO" table ( "(" column ("," column)* ") )?"
                 "VALUES" "(" value ("," value)* ")" ";" ;
column         → IDENTIFIER
table          → IDENTIFIER
value          → NUMBER | STRING | BOOLEAN
type          → INT | STRING
```
