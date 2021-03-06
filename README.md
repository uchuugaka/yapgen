# yapgen - parser generator

Rapid prototyping parser generator.

## Parser generator features

Follows list of parser generator features.

### Feature list

* Generates parser lexical and syntactical analyzers based on input file.
* Lexical symbols are described by regular expressions.
* Language grammar is described by SLR(1) grammar.
* Generated parser can be immediately tested on source string.
* Semantic rules of language can be tested by Lua scripts, that are binded to
  each rule reduction.
* Debugged and fine tuned parser can be generated in form of C/C++ code.

## Motivation

Need for fast parser generation and testing.

## Rule examples

Examples of rule files used to generate parsers are placed in directory:
[`yapgen_build/rules`](https://github.com/izuzanak/yapgen/tree/master/yapgen_build/rules)

### Inline examples

Follows few simple examples demonstrating yapgen possibilities.

#### Regular expressions

Examples of basic regular expressions.

```
oct_int     {'0'.<07>*}
dec_int     {<19>.d*}
hex_int     {'0'.[xX].(<09>+<af>+<AF>).(<09>+<af>+<AF>)*}

if          {"if"}
else        {"else"}

equal       {'='}
plus_equal  {"+="}
minus_equal {"-="}

comment_sl  {"//".!'\n'*.'\n'}
comment_ml  {"/*".(!'*'+('*'.!'/'))*."*/"}
```

Regular expressions can be used to recognize binary data.

```
PACKET_ADDRESS     {"/?".(<09>+<az>+<AZ>)*.'!'."\x0d\x0a"}
PACKET_IDENTIFY    {'/'.<AZ>.<AZ>.(<AZ>+<az>).<09>.(|/!\x0d|)*."\x0d\x0a"}
PACKET_ACK_COMMAND {'\x06'.<09>.(<09>+<az>).<09>."\x0d\x0a"}
PACKET_ACK         {'\x06'}
```

#### Grammar rules

Example of basic grammar rules. Identifiers closed in angle (sharp) brackets
e.g. `<command>` identifies nonterminal symbols of grammar, and identifiers
without brackets e.g. `if` refers to terminal symbols described by regular
expressions.

```
<command> -> if <condition> <if_else> ->> {}
<if_else> -> <command> ->> {}
<if_else> -> <command> else <command> ->> {}

<command> -> <while_begin> <condition> <command> ->> {}
<while_begin> -> while ->> {}
```

Grammar rules can have semantic code binded to them.

```
<F> -> <F> double_equal <E> ->>
{
  if gen_parse_tree == 1 then
     this_idx = node_idx;
     node_idx = node_idx + 1;
     print("   node_"..this_idx.." [label = \"<exp> == <exp>\"]");
     print("   node_"..this_idx.." -> node_"..table.remove(node_stack).."");
     print("   node_"..this_idx.." -> node_"..table.remove(node_stack).."");
     table.insert(node_stack,this_idx);
  else
     print(table.concat(tabs,"").."operator binary double_equal");
  end
}
```

#### Parser rule file

Follows example of complete parser rules file.

```
init_code: {s = {\};}

terminals:
  oct_int_const {'0'.<07>*}
  dec_int_const {<19>.d*}
  hex_int_const {'0'.[xX].(<09>+<af>+<AF>).(<09>+<af>+<AF>)*}

  lr_br    {'('}
  rr_br    {')'}

  plus     {'+'}
  minus    {'-'}
  asterisk {'*'}
  slash    {'/'}
  percent  {'%'}

  _SKIP_   {w.w*}
  _END_    {'\0'}

nonterminals:
  <start> <exp> <C> <B> <A>

rules:
  <start> -> <exp> _END_  ->> {}
  <exp> -> <C>            ->> {print("result: "..s[#s]);}
  <C> -> <C> plus <B>     ->> {s[#s-1] = s[#s-1] + table.remove(s);}
  <C> -> <C> minus <B>    ->> {s[#s-1] = s[#s-1] - table.remove(s);}
  <C> -> <B>              ->> {}
  <B> -> <B> asterisk <A> ->> {s[#s-1] = s[#s-1] * table.remove(s);}
  <B> -> <B> slash <A>    ->> {s[#s-1] = s[#s-1] / table.remove(s);}
  <B> -> <B> percent <A>  ->> {s[#s-1] = s[#s-1] % table.remove(s);}
  <B> -> <A>              ->> {}
  <A> -> lr_br <C> rr_br  ->> {}
  <A> -> oct_int_const    ->> {table.insert(s,tonumber(rule_body(0),8));}
  <A> -> dec_int_const    ->> {table.insert(s,tonumber(rule_body(0),10));}
  <A> -> hex_int_const    ->> {table.insert(s,tonumber(rule_body(0)));}
```

Parser generated from presented rule string will generate following result
for following input string.

```
5*(10 + 5) - 0x10
```
```
result: 59
```

## Building parser generator

Programming language Lua of version [5.2](http://www.lua.org/ftp/) or greater
is required for yapgen compilation.

Container generator [`cont`](https://github.com/izuzanak/cont) is needed for
compilation of parser generator. It will be automatically compiled in following
compilation steps.

### Linux compilation

For compilation of parser generator on Linux OS perform following steps:

  * Download script [`try_yapgen.sh`](https://raw.githubusercontent.com/izuzanak/yapgen/master/yapgen_try/try_yapgen.sh).

```
wget https://raw.githubusercontent.com/izuzanak/yapgen/master/yapgen_try/try_yapgen.sh
```

  * Check prerequisites mentioned in script.
  * Execute script `try_yapgen.sh`.

```
bash try_yapgen.sh
```

It will clone two repositories `cont` and `yapgen`, and subsequently compile
container generator and parser generator.

### Linux example parsers

Example parsers are located in directory
[yapgen_build/rules](https://github.com/izuzanak/yapgen/tree/master/yapgen_build/rules).
Names of parsers to be tested should be given as command line argument of
`try_yapgen.sh` script.  List of example parsers can be found at the end of
script `try_yapgen.sh`.

```
bash try_yapgen.sh demo_exp
```

