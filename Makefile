.DEFAULT_GOAL := build

.PHONY: build
build: format
	@./scripts/build.sh

.PHONY: format
format:
	@./scripts/format.sh

.PHONY: run
run: format
	@./scripts/build.sh
	@./build/tmpCoin