#ifndef CXX_PARSER_H
#define CXX_PARSER_H

#include <string>
#include <vector>

#include "data/parser/Parser.h"

class CanonicalFilePathCache;
class CxxDiagnosticConsumer;
class FilePath;
class FileRegister;
class IndexerCommandCxx;
class TaskParseCxx;
class TextAccess;

namespace clang {
	namespace tooling {
		class CompilationDatabase;
		class FixedCompilationDatabase;
	}
}

class CxxParser: public Parser
{
public:
	CxxParser(std::shared_ptr<ParserClient> client, std::shared_ptr<FileRegister> fileRegister);

	void buildIndex(std::shared_ptr<IndexerCommandCxx> indexerCommand);
	void buildIndex(const std::wstring& fileName, std::shared_ptr<TextAccess> fileContent, std::vector<std::wstring> compilerFlags = {});

private:
	void runTool(clang::tooling::CompilationDatabase* compilationDatabase, const FilePath& sourceFilePath);

	std::vector<std::string> getCommandlineArgumentsEssential(
		const std::vector<std::wstring>& compilerFlags,
		const std::vector<FilePath>& systemHeaderSearchPaths,
		const std::vector<FilePath>& frameworkSearchPaths) const;

	std::shared_ptr<CxxDiagnosticConsumer> getDiagnostics(
		const FilePath& sourceFilePath, std::shared_ptr<CanonicalFilePathCache> canonicalFilePathCache, bool logErrors) const;

	friend class TaskParseCxx;

	std::shared_ptr<FileRegister> m_fileRegister;

};

#endif // CXX_PARSER_H
