# recompile version.h dependants when GIT_VERSION changes, uses temporary file version~
.PHONY: force
../Application/Inc/git.h: force
	@echo "//----------------------------------------------------------------------" > $@
	@echo "// Titel	:	Git.h" >> $@
	@echo "//----------------------------------------------------------------------" >> $@
	@echo "// Sprache	:	C" >> $@
	@echo "// Datum	:	18.08.2021" >> $@
	@echo "// Version	:	1.0" >> $@
	@echo "// Autor	:	Diveturtle93" >> $@
	@echo "// Projekt	:	STM32F767ZI" >> $@
	@echo "//----------------------------------------------------------------------" >> $@
	@echo "" >> $@
	@echo "// Dateiheader definieren" >> $@
	@echo "//----------------------------------------------------------------------" >> $@
	@echo "#ifndef _GIT_H_" >> $@
	@echo "#define _GIT_H_" >> $@
	@echo "//----------------------------------------------------------------------" >> $@
	@echo "" >> $@
	@echo "// Git Commit-Infos definieren" >> $@
	@echo "//----------------------------------------------------------------------" >> $@
	@echo "#define GIT_COMMIT					\"$(shell git rev-parse --short HEAD)\"" >> $@
	@echo "#define GIT_BRANCH					\"$(shell git branch --show-current)\"" >> $@
	@echo "#define GIT_HASH					\"$(shell git rev-parse HEAD)\"" >> $@
	@echo "//----------------------------------------------------------------------" >> $@
	@echo "" >> $@
	@echo "// Git Tags-Infos definieren" >> $@
	@echo "//----------------------------------------------------------------------" >> $@
	@echo "#define GIT_LAST_TAG				\"$(shell git tag)\"" >> $@
	@echo "#define GIT_TAG_COMMIT				\"$(shell git rev-list --tags --abbrev-commit)\"" >> $@
	@echo "#define GIT_TAG_DIRTY				\"$(shell git describe)\"" >> $@
	@echo "//----------------------------------------------------------------------" >> $@
	@echo "" >> $@
	@echo "// Git Zaehler definieren" >> $@
	@echo "//----------------------------------------------------------------------" >> $@
	@echo "#define GIT_TAG_DIRTY_COUNT			\"$(shell git rev-list  `git rev-list --tags --no-walk --max-count=1`..HEAD --count)\"" >> $@
	@echo "#define GIT_OVERALL_COMMIT_COUNT	\"$(shell git rev-list --all --count)\"" >> $@
	@echo "#define GIT_BRANCH_COMMIT_COUNT		\"$(shell git rev-list --count `git branch --show-current`)\"" >> $@
	@echo "#define GIT_ACTIVE_BRANCHES			\"$(shell git branch | wc -l)\"" >> $@
	@echo "#define GIT_TAG_COUNT				\"$(shell git rev-list --tags --count)\"" >> $@
	@echo "//----------------------------------------------------------------------" >> $@
	@echo "" >> $@
	@echo "// Build Zeit definieren" >> $@
	@echo "//----------------------------------------------------------------------" >> $@
	@echo "#define BUILD_DATE					\"$(shell date +"%Y-%m-%d")\"" >> $@
	@echo "#define BUILD_TIME					\"$(shell date +"%H:%M:%S")\"" >> $@
	@echo "//----------------------------------------------------------------------" >> $@
	@echo "#endif /* _GIT_H_ */" >> $@
	@echo "//----------------------------------------------------------------------" >> $@