# ~/.bashrc: executed by bash(1) for non-login shells.

###### this is for synology, that runs an old version of bash masked as /bin/sh.
# if we're running on a Synology, and are called as "-sh", don't do anything.
[[ -f /etc/synoinfo.conf ]] && [[ "$0" == "-sh" ]] && return 0

#interactive_session=$(expr index "$-" i)
interactive_session=0
[[ $- == *i* ]] && interactive_session=1

if [[ $interactive_session -eq 1 && -x "$(command -v fastfetch)" ]]; then
  fastfetch
fi

# see /usr/share/doc/bash/examples/startup-files (in the package bash-doc)
# for examples

# If not running interactively, don't do anything
case $- in
  *i*) ;;
  *) return;;
esac

# if running with home-manager, do init
[[ -f "$HOME/.nix-profile/etc/profile.d/hm-session-vars.sh" ]] && source "$HOME/.nix-profile/etc/profile.d/hm-session-vars.sh"

# don't put duplicate lines or lines starting with space in the history.
# See bash(1) for more options
export HISTCONTROL=erasedups:ignoredups:ignorespace

# for setting history length see HISTSIZE and HISTFILESIZE in bash(1)
export HISTSIZE=1000
export HISTFILESIZE=10000

# Check the window size after each command and, if necessary, update the values of LINES and COLUMNS
shopt -s checkwinsize

# append to the history file, don't overwrite it
shopt -s histappend
PROMPT_COMMAND='history -a'

# Color for manpages in less makes manpages a little easier to read
export LESS_TERMCAP_mb=$'\E[01;31m'
export LESS_TERMCAP_md=$'\E[01;31m'
export LESS_TERMCAP_me=$'\E[0m'
export LESS_TERMCAP_se=$'\E[0m'
export LESS_TERMCAP_so=$'\E[01;44;33m'
export LESS_TERMCAP_ue=$'\E[0m'
export LESS_TERMCAP_us=$'\E[01;32m'

# Ignore case on auto-completion
# Note: bind used instead of sticking these in .inputrc
if [[ $interactive_session -eq 1 ]]; then bind "set completion-ignore-case on"; fi

# Show auto-completion list automatically, without double tab
if [[ $interactive_session -eq 1 ]]; then bind "set show-all-if-ambiguous On"; fi

# If set, the pattern "**" used in a pathname expansion context will
# match all files and zero or more directories and subdirectories.
#shopt -s globstar

# make less more friendly for non-text input files, see lesspipe(1)
lesspipe_path=$(which lesspipe.sh 2>/dev/null)
[ -n "$lesspipe_path" ] && eval "$($lesspipe_path)"

# set variable identifying the chroot you work in (used in the prompt below)
if [ -z "${debian_chroot:-}" ] && [ -r /etc/debian_chroot ]; then
  debian_chroot=$(cat /etc/debian_chroot)
fi

# set a fancy prompt (non-color, unless we know we "want" color)
case "$TERM" in
  xterm-color|*-256color) color_prompt=yes;;
esac

# uncomment for a colored prompt, if the terminal has the capability; turned
# off by default to not distract the user: the focus in a terminal window
# should be on the output of commands, not on the prompt
#force_color_prompt=yes

if [ -n "$force_color_prompt" ]; then
  if [ -x /usr/bin/tput ] && tput setaf 1 >&/dev/null; then
    # We have color support; assume it's compliant with Ecma-48
    # (ISO/IEC-6429). (Lack of such support is extremely rare, and such
    # a case would tend to support setf rather than setaf.)
    color_prompt=yes
  else
    color_prompt=
  fi
fi

if [ "$color_prompt" = yes ]; then
  PS1='\D{%H:%M:%S} ${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
else
  PS1='\D{%H:%M:%S} ${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
fi
unset color_prompt force_color_prompt

# If this is an xterm set the title to user@host:dir
case "$TERM" in
  xterm*|rxvt*)
    PS1="\[\e]0;${debian_chroot:+($debian_chroot)}\u@\h: \w\a\]$PS1"
    ;;
  *)
    ;;
esac

#############
# set DISPLAY from ssh
# Check if the SSH_CONNECTION variable is set
if [[ -n "$SSH_CONNECTION" ]]; then
  # Extract the first IP address (assuming it's the first element before the first space)
  ip_address=$(echo "$SSH_CONNECTION" | awk '{print $1}')
  #
  # Set the DISPLAY environment variable with ':10' appended
  export DISPLAY="${ip_address}:10"
fi

export EDITOR='nvim'
export PIPEWIRE_LATENCY=256/48000
export MOZ_ENABLE_WAYLAND=1 #wha????
export XDG_CONFIG_HOME="$HOME/.config"
export LESS=Sni#20

### for PodMan
if [[ -z "$XDG_RUNTIME_DIR" ]]; then
  export XDG_RUNTIME_DIR=/run/user/$UID
  if [[ ! -d "$XDG_RUNTIME_DIR" ]]; then
    export XDG_RUNTIME_DIR=/tmp/$USER-runtime
    if [[ ! -d "$XDG_RUNTIME_DIR" ]]; then
      mkdir -m 0700 "$XDG_RUNTIME_DIR"
    fi
  fi
fi
# stuff to do before mass-sourcing
# install FZF if needed
if [ ! -f "$HOME/.fzf.bash" ]; then
  git clone --depth 1 https://github.com/junegunn/fzf.git ~/.fzf
  ~/.fzf/install
fi
# init fzf
export FZF_DEFAULT_OPTS=" \
--color=bg+:#313244,bg:#1e1e2e,spinner:#f5e0dc,hl:#f38ba8 \
--color=fg:#cdd6f4,header:#f38ba8,info:#cba6f7,pointer:#f5e0dc \
--color=marker:#b4befe,fg+:#cdd6f4,prompt:#cba6f7,hl+:#f38ba8 \
--color=selected-bg:#45475a \
--multi"

export NVM_DIR="$HOME/.nvm"

# traverse through paths and initialize if present
initializations=(
  "$HOME/.asdf/asdf.sh"
  "$HOME/.bash_aliases"
  "$HOME/.cargo/env"
  "$HOME/.dotfiles/bash/.bash_aliases"
  "$HOME/.env.sh"
  "$HOME/.fzf.bash"
  "$HOME/lua51/bin/activate"
  "$NVM_DIR/bash_completion"
  "$NVM_DIR/nvm.sh"
  "/etc/bash_completion"
  "/usr/share/bash-completion/bash_completion"
)
for inits in "${initializations[@]}"; do
  if [ -f "$inits" ]; then
    source "$inits"
    # echo "sourcing $inits"
  fi
done

# now do paths
paths=(
  "/usr/local/go/bin"
  "/var/lib/flatpak/exports/bin"
  "$HOME/.local/share/flatpak/exports/bin"
  "$HOME/go/bin/"
  "$HOME/.cargo/bin/"
  "$HOME/.local/bin/"
)

for dir in "${paths[@]}"; do
  if [ -d "$dir" ]; then
    export PATH="$dir:$PATH"
  fi
done

# If ripgrep envvar is unset,
# if ripgrep config is prewsent,
# init ripgrep env
  [[ -z "${RIPGREP_CONFIG_PATH}" ]] &&
    [[ -f ".config/ripgrep/config" ]] && export RIPGREP_CONFIG_PATH=~/.config/ripgrep/config

command -v zoxide &>/dev/null || \
  (curl -sSfL https://raw.githubusercontent.com/ajeetdsouza/zoxide/main/install.sh | sh)
eval "$(zoxide init bash)"

hostname=$(hostname)
export COMPUTERNAME=$hostname

export KANATA_LAYOUT=kinesis
if command -v lsmod >/dev/null; then
  if lsmod | grep -q 'hv_vmbus'; then
    export KANATA_PLATFORM=hyperv
  else
    export KANATA_PLATFORM=hardware
  fi
fi

command -v starship &>/dev/null || \
  (curl -sS https://starship.rs/install.sh | sh)
eval "$(starship init bash)"

if [ -f ~/.dotfiles/check-git.sh ]; then
  bash  ~/.dotfiles/check-git.sh
fi

##### finally
# if command -v tmux >/dev/null; then
#   if [[ $TERM_PROGRAM != "tmux" ]]; then
#     if [[ $SSH_CONNECTION ]]; then
#       exec tmux attach
#     fi
#   fi
# fi

# Smart Yazi starter, ends in currently selected directory
[[ -z "${YAZI_CONFIG_HOME}" ]] && export YAZI_CONFIG_HOME=~/.config/yazi/
function yy() {
  local tmp="$(mktemp -t "yazi-cwd.XXXXXX")"
  yazi "$@" --cwd-file="$tmp"
  if cwd="$(cat -- "$tmp")" && [ -n "$cwd" ] && [ "$cwd" != "$PWD" ]; then
    cd -- "$cwd" || exit 
  fi
  rm -f -- "$tmp"
}
# export JUST_JUSTFILE="$HOME/.justfile"
function j() {
    if [ -f ./justfile ] || [ -f ./.justfile ]; then
        just "$@"
    else
        just --justfile "${HOME}/.justfile" "$@"
    fi
}

# tre
tre() { command tre "$@" -e && source "/tmp/tre_aliases_$USER" 2>/dev/null; }

# Bind the function to Ctrl+.
bind -x '"\C-\.": "yy"'


[ -f ~/.fzf.bash ] && source ~/.fzf.bash
