from argparse import ArgumentParser
from pathlib import Path


MAIN_FILE = "main.cpp"
MAIN_FILE_CONTENT = """\
#include <iostream>

int main() {
  return 0;
}
"""


def create_task_folder(new_task_name: str, tests_count: int) -> None:
    words = new_task_name.lower().strip().split()

    task_path = Path("solutions") / Path("-".join(words))
    task_path.mkdir()

    with open(task_path / MAIN_FILE, "w") as file:
        file.write(MAIN_FILE_CONTENT)

    tests_path = task_path / Path("tests")
    tests_path.mkdir()

    for i in range(tests_count):
        with open(tests_path / f"input.{i+1}.txt", mode="a"):
            pass
        with open(tests_path / f"output.{i+1}.txt", mode="a"):
            pass


if __name__ == "__main__":
    parser = ArgumentParser()
    parser.add_argument("task_name", type=str)
    parser.add_argument("--tests", type=int, default=1, required=False)
    args = parser.parse_args()

    create_task_folder(args.task_name, args.tests)
