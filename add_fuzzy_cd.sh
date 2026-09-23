#!/usr/bin/env bash
set -euo pipefail

# Usage add_fuzzy_cd FUNC_NAME DIRECTORY
# Example: add_fuzzy_cd cdp ~/Projects

if [[ $# -ne 2 ]]; then
    echo "Usage: $0 FUNC_NAME DIRECTORY" >&2
    exit 1
fi

FUNC_NAME=$1
DIR_INPUT=$2

if ! [[ $FUNC_NAME =~ ^[a-zA-Z_][a-zA-Z0-9_]*$ ]]; then
    echo "Invalid function name: $FUNC_NAME" >&2
    echo "Function name must match: ^[a-zA-Z_][a-zA-Z0-9_]*$" >&2
    exit 1
fi

if ! DIR_ABS=$(cd "$DIR_INPUT" 2>/dev/null && pwd); then
    echo "Directory does not exist: $DIR_INPUT" >&2
    exit 1
fi

BASHRC="${HOME}/.bashrc"
FCD_CMD="${FCD_CMD:-fuzzySearch}"

cat >> "$BASHRC" <<EOF

# Auto-generated fuzzy cd function: $FUNC_NAME -> $DIR_ABS
$FUNC_NAME() {
    local target

    target="\$(
        $FCD_CMD \\
            "$DIR_ABS" \\
            "\$1"
    )" || return \$?

    cd -- "\$target"
}
EOF

echo "Added function '$FUNC_NAME' for directory '$DIR_ABS' to $BASHRC"
echo "Run:  source \"$BASHRC\"  to load it in your current shell."