#include "artifact.h"

std::string Artifact::GenHash() {
  srand((unsigned)time(nullptr));

  constexpr std::string_view alphanum = "0123456789"
                                        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                        "abcdefghijklmnopqrstuvwxyz";
  std::string hash;
  hash.reserve(30);

  for (int i = 0, end = 30; i < end; ++i) {
    hash += alphanum[rand() % alphanum.size()];
  }

  return hash;
}

void Artifact::CreateArtifact(const std::vector<std::string> &filenames) {
  const auto config = std::make_unique<Config>();
  config->LoadConfig();

  std::string artifactComment;
  do {
    std::cout << "Enter artifact comment: ";
    std::getline(std::cin, artifactComment);
  } while (artifactComment.empty());

  std::cout << "[stardust-info]: Processing files..." << std::endl;

  const auto breakthroughPath = config->getBasePath().string() +
                                "/breakthroughs/" +
                                config->getCurrentBreakthrough();
  const auto archiveHash = GenHash();

  {
    const std::unique_ptr<Tarfful::Tar> archive =
        std::make_unique<Tarfful::Tar>(breakthroughPath + "/artifacts/" +
                                       archiveHash + ".tar");

    std::ifstream ignoreFile(config->getBasePath().parent_path().string() +
                             "/.stardust-ignore");
    std::vector<std::string> ignorableFiles;
    std::string file_entry;
    while (std::getline(ignoreFile, file_entry)) {
      ignorableFiles.emplace_back(file_entry);
    }
    ignoreFile.close();

    for (const auto &file : filenames) {
      if (std::count_if(ignorableFiles.begin(), ignorableFiles.end(),
                        [&file](auto const &s) {
                          return s.find(file) != std::string::npos;
                        })) {
        continue;
      }

      if (fs::is_directory(file)) {
        archive->ArchiveDirectoryContent(file);
      } else {
        archive->ArchiveFile(file);
      }
    }
  }

  std::ofstream artifactsList;
  artifactsList.open(breakthroughPath + "/.artifactsList",
                     std::ios::out | std::ios::app);
  const time_t now = time(nullptr);
  const char *dt = ctime(&now);

  artifactsList << "Hash: " << archiveHash << '\n';
  artifactsList << "Comment: " << artifactComment << '\n';
  artifactsList << "Created at: " << dt << '\n';

  std::cout << "[stardust-success]: Created new artifact with hash "
            << archiveHash << '\n';
}

void Artifact::PrintArtifactsLog() {
  const auto config = std::make_unique<Config>();
  config->LoadConfig();

  const auto artifactsListPath =
      fs::absolute(config->getBasePath().string() + "/breakthroughs/" +
                   config->getCurrentBreakthrough())
          .string() +
      "/.artifactsList";

  std::ifstream file;
  file.open(artifactsListPath, std::ios::in);

  std::stringstream logFileContent;
  logFileContent << file.rdbuf();

  std::cout << "# The lowest artifact is the latest #\n\n";
  std::cout << "Project: " << config->getProjectName() << '\n';
  std::cout << "Current breakthrough: " << config->getCurrentBreakthrough()
            << "\n";
  std::cout << "Artifacts list: \n\n";
  std::cout << logFileContent.str();
}

void Artifact::RevertArtifact(const std::string &hash) {
  const auto config = std::make_unique<Config>();
  config->LoadConfig();
  fs::current_path(config->getBasePath().parent_path());

  const auto artifactPath = fs::absolute(
      fs::current_path().string() + "/.stardust/breakthroughs/" +
      config->getCurrentBreakthrough() + "/artifacts/" + hash + ".tar");
  std::cout << artifactPath << '\n';
  if (fs::exists(artifactPath)) {
    std::cout << "[stardust-info]: Processing files...\n";
    const std::unique_ptr<Tarfful::Tar> archive =
        std::make_unique<Tarfful::Tar>(artifactPath);
    archive->ExtractAll();
  } else {
    throw std::runtime_error(std::string(Messages::ARTIFACT_NOT_FOUND));
  }

  std::cout << "[stardust-success]: Reverted data from artifact " << hash
            << '\n';
}