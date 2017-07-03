01-println: .FORCE
	#
	# Cleanup.
	rm -f $@
	#
	# Simple run.
	go run $@.go
	#
	# Show WORK directory.
	go run --work $@.go
	#
	# Executable is not created in current directory by 'go run'.
	[ -e $@ ] && echo Executable exists || echo Executable does not exist
	#
	# Build an executable in the current directory.
	go build $@.go
	./$@
	#
	# Check source code format.
	gofmt -d $@.go

02-import \
04-var \
05-func \
06-underscore \
07-struct \
08-pointer \
09-method \
10-factory \
11-new \
12-composition \
13-overriding \
14-array \
15-slice \
16-slice-cap \
17-slice-init \
18-slice-wrapper \
19-map \
25-interface \
26-interface-composition \
27-error \
29-defer \
30-initialized-if \
31-conversions \
32-switch-type \
33-bytes \
34-func-type \
35-goroutine \
36-sync-none \
37-sync-mutex \
38-chan \
39-multiple-workers \
40-blocking-worker \
41-buffered-chan \
42-select \
43-timeout \
44-timeout-drop \
45-timeout-value \
: .FORCE
	go run $@.go
	gofmt -d $@.go

03-imports: .FORCE
	go run $@.go foo
	gofmt -d $@.go
	go build $@.go
	./$@ bar

20-package: .FORCE
	#
	# Without setting GOPATH, the following error occurs.
	#
	# 20-package.go:5:2: cannot find package "shopping" in any of:
	# 	/usr/lib/go/src/pkg/shopping (from $GOROOT)
	# 	($GOPATH not set)
	#
	-go run $@.go
	#
	# GOPATH must be set to the absolute path of the directory that
	# contains the 'src' directory within which packages reside.
	#
	GOPATH=$(PWD)/go go run $@.go

21-package-consistency: .FORCE
	GOPATH=$(PWD)/go go run $@.go
	gofmt -d $@.go go/src/pkg21*

22-package-naming: .FORCE
	GOPATH=$(PWD)/go go run $@.go
	gofmt -d $@.go go/src/22-pkg

23-package-visibility: .FORCE
	GOPATH=$(PWD)/go go run $@.go
	gofmt -d $@.go go/src/23-pkg

24-go-get: .FORCE
	#
	# --------------------------------------------
	# If `git push` fails,
	#
	#   1. Go to BitBucket.
	#   2. Create a public repository named gofoo.
	# --------------------------------------------
	#
	# Pushing 24-gofoo to BitBucket ...
	sh 24-gofoo/git-push.sh
	#
	#
	# TEST 1
	# ------
	rm -rf tmpgo1
	GOPATH=$(PWD)/tmpgo1 go get bitbucket.org/susam/gofoo
	tree tmpgo1
	GOPATH=$(PWD)/tmpgo1 go run $@.go
	#
	#
	# TEST 2
	# ------
	rm -rf tmpgo2
	mkdir -p tmpgo2/src/24-go-get
	ln -s ../../../24-go-get.go tmpgo2/src/24-go-get
	cd tmpgo2/src/24-go-get && GOPATH=$(PWD)/tmpgo2 go get
	tree tmpgo2
	tmpgo2/bin/24-go-get
	cd tmpgo2/src/24-go-get && GOPATH=$(PWD)/tmpgo2 go run 24-go-get.go
	#
	# Go format
	gofmt -d $@.go 24-gofoo

28-scan: .FORCE
	# ------
	echo 10 20 foo | go run $@.go
	# ------
	echo 30 40 | go run $@.go
	# ------
	echo foo bar baz | go run $@.go
	# ------
	go run $@.go < /dev/null
	# ------
	gofmt -d $@.go
	
clean:
	find -type f ! -name "*.go" ! -name "Makefile" ! -name "README.md" ! -name "*.swp" ! -name "*.sh" -exec rm -f {} \;
	rm -rf tmpgo1 tmpgo2
	rm -rf 24-gofoo/.git

count:
	ls *.go | wc -l

.FORCE:
# vim: noet
