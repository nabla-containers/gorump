package main

import "fmt"
import "C"
import "os"

func main() {
    damain()
}

func damain() {
    fmt.Println("Hello, Rumprun.  This is Go.")
    args := os.Args[1:]
    fmt.Println("got commandline args:")
    fmt.Println(args)
    fmt.Println("last commandline arg:")
    fmt.Println(args[len(args)-1])
}
