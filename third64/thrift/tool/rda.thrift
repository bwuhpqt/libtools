namespace cpp rda


#word info
struct Token
{
1: string word,
2: i32 offset,
3: i32 len,
4: string pos,
5: string deprel,
6: string meaning,
7: i32 head;
8: i32 type,
9: list<string> tags,
}


struct Session
{
1: optional string query
}


#input
struct AIRequest
{
1: required string query,
2: optional string production,
3: optional string clientid,
4: optional string timestamp,
5: optional map<string, string> ext_input,
6: optional Session session,
}


#ouput
struct AIResponse
{
1: i32 status,
2: optional string query,
3: optional list<Token> token_list,

}


service Serv{
	AIResponse rda(1: AIRequest request),
}


