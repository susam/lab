import pytest
from skippy import (
    ParseError,
    TType,
    Token,
    parse,
    tokenize,
)


def test_tokenize_empty():
    assert tokenize("", "foo.sk") == []
    assert tokenize(" ", "foo.sk") == []
    assert tokenize("\n", "foo.sk") == []


def test_tokenize_positive_integer():
    assert tokenize("1", "foo.sk") == [
        Token(1, TType.INTEGER, "foo.sk", 1, 1)
    ]
    assert tokenize("10", "foo.sk") == [
        Token(10, TType.INTEGER, "foo.sk", 1, 1)
    ]


def test_tokenize_zero():
    assert tokenize("0", "foo.sk") == [
        Token(0, TType.INTEGER, "foo.sk", 1, 1)
    ]
    assert tokenize("-0", "foo.sk") == [
        Token(0, TType.INTEGER, "foo.sk", 1, 1)
    ]


def test_tokenize_negative_integer():
    assert tokenize("-1", "foo.sk") == [
        Token(-1, TType.INTEGER, "foo.sk", 1, 1)
    ]
    assert tokenize("-10", "foo.sk") == [
        Token(-10, TType.INTEGER, "foo.sk", 1, 1)
    ]


def test_tokenize_empty_list():
    assert tokenize("()", "foo.sk") == [
        Token("(", TType.LPAREN, "foo.sk", 1, 1),
        Token(")", TType.RPAREN, "foo.sk", 1, 2),
    ]


def test_tokenize_expression_list():
    assert tokenize("(+ 1 2)", "foo.sk") == [
        Token("(", TType.LPAREN, "foo.sk", 1, 1),
        Token("+", TType.SYMBOL, "foo.sk", 1, 2),
        Token(1, TType.INTEGER, "foo.sk", 1, 4),
        Token(2, TType.INTEGER, "foo.sk", 1, 6),
        Token(")", TType.RPAREN, "foo.sk", 1, 7),
    ]


def test_tokenize_arbitrary_list():
    assert tokenize("( foo bar 10.2 )", "foo.sk") == [
        Token("(", TType.LPAREN, "foo.sk", 1, 1),
        Token("foo", TType.SYMBOL, "foo.sk", 1, 3),
        Token("bar", TType.SYMBOL, "foo.sk", 1, 7),
        Token(10.2, TType.FLOAT, "foo.sk", 1, 11),
        Token(")", TType.RPAREN, "foo.sk", 1, 16),
    ]


def test_tokenize_arbitrary_list_newline():
    assert tokenize("( foo\nbar baz\n    qux)", "foo.sk") == [
        Token("(", TType.LPAREN, "foo.sk", 1, 1),
        Token("foo", TType.SYMBOL, "foo.sk", 1, 3),
        Token("bar", TType.SYMBOL, "foo.sk", 2, 1),
        Token("baz", TType.SYMBOL, "foo.sk", 2, 5),
        Token("qux", TType.SYMBOL, "foo.sk", 3, 5),
        Token(")", TType.RPAREN, "foo.sk", 3, 8),
    ]


def test_tokenize_integer_newline():
    assert tokenize("\n10", "foo.sk") == [
        Token(10, TType.INTEGER, "foo.sk", 2, 1),
    ]


def test_parse_empty():
    with pytest.raises(ParseError) as exc_info:
        parse([])
    assert str(exc_info.value) == "error: empty source"


def test_parse_lparen():
    with pytest.raises(ParseError) as exc_info:
        parse([
            Token("(", TType.LPAREN, "foo.sk", 1, 1),
        ])
    assert str(exc_info.value) == "foo.sk:1:1: error: unexpected eof"


def test_parse_rparen():
    with pytest.raises(ParseError) as exc_info:
        parse([
            Token(")", TType.LPAREN, "foo.sk", 1, 1),
        ])
    assert str(exc_info.value) == "foo.sk:1:1: error: unexpected eof"


def test_parse_expression():
    assert parse(
        [
            Token("(", TType.LPAREN, "foo.sk", 1, 1),
            Token("+", TType.SYMBOL, "foo.sk", 1, 10),
            Token("10", TType.INTEGER, "foo.sk", 1, 20),
            Token("2.1", TType.FLOAT, "foo.sk", 1, 30),
            Token(")", TType.RPAREN, "foo.sk", 1, 40),
        ]
    ) == [
        Token("+", TType.SYMBOL, "foo.sk", 1, 10),
        Token("10", TType.INTEGER, "foo.sk", 1, 20),
        Token("2.1", TType.FLOAT, "foo.sk", 1, 30),
    ]
