alias btop='sudo btop'
#alias cp='cp -i'
alias fzp='fzf --preview "bat --color=always --style=numbers --line-range=:500 {}"'
alias hf='history|grep -i '
alias ifconfig='curl -i http://ifconfig.me/all && echo'
alias less='less -Si#20 '
alias ll='ls -alhF'
alias lsd='ls -alhF|rg ^d'
alias lsl='ls -alhF|rg ^l'
alias mkdir='mkdir -p'
alias mv='mv -i'
alias mtr='sudo -E mtr'
alias napf='sudo -E netstat -nap|rg '
alias napt='sudo -E netstat -napt'
alias napu='sudo -E netstat -napu'
alias pf='sudo -E ps -A|rg '
alias ping='sudo -E ping'
alias sf='env|rg '
alias vbrc='nvim ~/.bashrc'
alias v='nvim'
alias V='sudo -E nvim'

# Change directory aliases
alias home='cd ~'
alias cd..='cd ..'
alias ..='cd ..'
alias ...='cd ../..'
alias ....='cd ../../..'
alias .....='cd ../../../..'

alias docker-clean=' \
  docker container prune -f ; \
  docker image prune -f ; \
  docker network prune -f ; \
  docker volume prune -f '

# Copy file with a progress bar
cpp() {
  set -e
  strace -q -ewrite cp -- "${1}" "${2}" 2>&1 |
    awk '{
  count += $NF
  if (count % 10 == 0) {
    percent = count / total_size * 100
    printf "%3d%% [", percent
    for (i=0;i<=percent;i++)
      printf "="
      printf ">"
      for (i=percent;i<100;i++)
        printf " "
        printf "]\r"
      }
    }
  END { print "" }' total_size="$(stat -c '%s' "${1}")" count=0
}

alias fullupgrade='sudo apt update && sudo apt full-upgrade --yes && sudo apt autoremove --yes --purge'
# Check if the distribution is fedora
if [ -f "/etc/os-release" ]; then
  if grep -qi 'fedora' /etc/os-release; then
    alias fullupgrade='yes|sudo dnf update && yes|sudo dnf upgrade && yes|sudo dnf autoremove'
  fi
fi

alias yyc='yazi /cifs/office-agoraphobia.lan/C/Users/bogorad/'
alias yys='yazi /cifs/syn.bruc'
