package simplelib_test

import (
	"github.com/ianco/simplelib"
	"testing"
)

func TestHello(t *testing.T) {
	c := simplelib.NewSimpleClass()
	s := c.Hello()
	if s != "world" {
		t.Error("unexpected value: ", s)
	}
}

func TestHelloString(t *testing.T) {
	c := simplelib.NewSimpleClass()
	v := simplelib.NewStringVector()
	c.HelloString(v)
	c.HelloString(v)
	if v.Size() != 2 {
		t.Error("incorrect size: ", v)
	}
}

func TestHelloBytes(t *testing.T) {
	c := simplelib.NewSimpleClass()
	v := simplelib.NewByteVector()
	c.HelloBytes(v)
	c.HelloBytes(v)
	if v.Size() != 10 {
		t.Error("incorrect size: ", v)
	}
}

func TestSimpleAdd(t *testing.T) {
	c := simplelib.NewSimpleClass()
	i := c.Add(1, 2);
	if i != 3 {
		t.Error("incorrect result: ", i);
	}
}

func TestMiscSqrtNumber(t *testing.T) {
	c := simplelib.NewMisc()
	i := c.Sqrt(64)
	if i != 8 {
		t.Error("incorrect result: ", i);
	}
}


