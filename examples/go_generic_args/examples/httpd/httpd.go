package main

import (
	"C"
	"fmt"
	"net/http"
	"time"
)

// fast test
func fastHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "this request is fast")
}

func main() { httpd() }

func httpd() {
	fmt.Println("hi; you can call `wget <ip>:3000/fast' now")
	http.HandleFunc("/fast", fastHandler)

	http.ListenAndServe(":3000", nil)

	time.Sleep(5 * time.Second)
	fmt.Println("yo")
}
